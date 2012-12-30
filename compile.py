#!/usr/bin/env python
from os import path, walk, symlink
from markdown import markdown
from datetime import datetime
from PyRSS2Gen import RSS2, RSSItem, Guid
from jinja2 import Environment, FileSystemLoader
from collections import defaultdict
import codecs

URL = 'http://theyearlyprophet.com/'
HOME = path.abspath(path.dirname(__file__))
ARTICLES_HOME = path.join(HOME, 'articles')
ASSETS_HOME = path.join(HOME, 'assets')
OUTPUT_HOME = path.join(HOME, 'output')
TEMPLATES_HOME = path.join(HOME, 'templates')

jinja_env = Environment(loader=FileSystemLoader(TEMPLATES_HOME))

def is_article(file):
    return file.lower().endswith('.md')

def scan_articles(): 
    articles, attachments = [], []
    for dir_path, __, files in walk(path.join(ARTICLES_HOME)):
        for file in files:
            if is_article(file):
                articles.append(path.join(dir_path, file))
            else:
                attachments.append(path.join(dir_path, file))
    return articles, attachments

def read_article(article_path):
    md_name = path.basename(article_path)
    html_name = '.'.join(md_name.split('.')[:-1] + ['html'])
    ret = {'source': article_path,
           'html_name': html_name,
           'dest': path.join(OUTPUT_HOME, html_name)}

    f = codecs.open(article_path, encoding='utf-8')
    
    for line in f:
        line = line.strip()
        if not line: break
        tokens = line.split(':')
        ret[tokens[0]] = ':'.join(tokens[1:]).strip()

    ret['categories'] = [s.strip() 
                         for s in ret.get('categories', '').split(',')]
    ret['body'] = f.read(1024*1024*1024)
    preview = ret['body'].split('<!-- PREVIEW_END -->')[0]
    if preview != ret['body']:
        preview += """

[[read more](%s%s)]""" % (URL, ret['html_name'])
    ret['markdown_preview'] = markdown(preview)
    ret['markdown'] = markdown(ret['body'])
    
    return ret

def process_article(article):
    template = jinja_env.get_template('article.html')
    codecs.open(article['dest'], 'w', encoding='utf-8').write(template.render(**article))

def generate_category_index(category_name, articles):
    dest = path.join(OUTPUT_HOME, category_name + '.html')
    template = jinja_env.get_template('category.html')
    rendered = template.render(category_name=category_name, articles=articles)
    codecs.open(dest, 'w', encoding='utf-8').write(rendered)

def generate_chronological_index(articles):
    dest = path.join(OUTPUT_HOME, 'chronological.html')
    template = jinja_env.get_template('chronological.html')
    rendered = template.render(articles=articles)
    codecs.open(dest, 'w', encoding='utf-8').write(rendered)

def generate_front_page(category_indexed, articles):
    dest = path.join(OUTPUT_HOME, 'index.html')
    template = jinja_env.get_template('index.html')
    rendered = template.render(category_indexed=category_indexed, articles=articles)
    codecs.open(dest, 'w', encoding='utf-8').write(rendered)

def generate_rss(articles):
    def to_datetime(ymd):
        y, m, d = map(int, ymd.split('-'))
        return datetime(y, m, d)
    rss = RSS2(title='The Yearly Prophet',
               link=URL,
               description='Technical blog/article archive of JongMan Koo',
               lastBuildDate=datetime.now(),
               items=[
                   RSSItem(title=article['title'],
                           link=URL + article['html_name'],
                           description=article['markdown_preview'],
                           guid=Guid(article['html_name']),
                           pubDate=to_datetime(article['date']))
                   for article in articles[:20]
               ])
    rss.write_xml(open(path.join(OUTPUT_HOME, 'rss.xml'), 'w'))


def generate_indices(articles):
    articles.sort(key=lambda a: a['date'])
    articles = list(reversed(articles))

    indexed = defaultdict(list)
    for article in articles: 
        for category in article['categories']:
            indexed[category].append(article)

    for category, category_articles in indexed.items():
        generate_category_index(category, category_articles)

    generate_chronological_index(articles)
    generate_front_page(indexed, articles)
    generate_rss(articles)

def process_articles(article_paths):

    articles = map(read_article, article_paths)

    for article in articles:
        process_article(article)

    generate_indices(articles)

def main():
    articles, attachments = scan_articles()

    process_articles(articles)
    assets_output = path.join(OUTPUT_HOME, 'assets')
    if not path.exists(assets_output):
        symlink(ASSETS_HOME, assets_output)
    # copy_attachments(attachments)

if __name__ == '__main__':
    main()
