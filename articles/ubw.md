title: 비공개: UBW
date: 2014-08-21
hidden: 1


What do you think of magic? Magic used to be a secretive and mysterious art, only known by a select few during the ancient era. However, modern-day magic is very different: it is very scientific, reproducible, and has a textual form. Maybe you have seen it, or have used it already. Here's an example:

	def main
	 loop 5
	  loop 3
	   Unlimited
	  Blade
	 Works

Modern day magic is defined by a **magic code**, which is composed of one or more **module** definitions. For example, the above magic defines a "main" module. A module contains a series of **operations**, which will be executed in order when the module is **invoked**. Each operation is either a **loop** or a **module invocation**. 

The operations that are contained by a module could be identified by a single space character (that is, indented by a single space) before the operation. Therefore, "main" module above consists of two operations; `loop 5` and `Works`. 

What do these operations do?

* An operation in the form of `loop N` contains one or more operations, and executes them $N$ times. You can identify the contained operations by looking for one more space in front of those operations; for example, `loop 5` operation above contains two operations `loop 3` and `Blade`. `loop 3` operation contains only a single operation, `Unlimited`.
* All other operations are in the form of `(module name)`, and they simply invoke the given module. After the invoked module terminates (all operations in the invoked module is executed), we will resume executing this module at the next operation. 

For example, `loop 3` operation above will invoke the module `Unlimited` 3 times, and then we will proceed to the next operation `Blade`. 

(For a concrete description on magic code, look below.)

Your friend in WinterTree city is an unpredictable guy. He makes blades for a living. Today he wrote a new magic code, which can be performed by invoking the "main" module. The main module will eventually call the module "Blade" 0 or more times - every time the "Blade" module is called, it will create a blade. However, he is not sure how many blades this magic is going to make. You, as one of his wizard friends, should help him to calculate how many blades will be created after unlimited time is passed.

### Magic code specification

* A **magic code** is a text file, consisting of multiple lines. 
	* Each line can be "indented" by one or more space characters.
	* Each line will contain 120 or less characters.
	* A magic code consists of one or more module definitions.
* A **module definition** begins with a line of the form "def (modulename)".
	* One or more lines follow, each containing a single operation indented by one or more spaces. Out of those, all operations that are indented by a single space are contained by this module.
	* A module name is a string of alphanumeric characters, shorter than 15 characters.
* An **operation** is either:
	* A **loop** operation in the form of `loop N`. 
		* One or more lines follow, each containing a single operation indented **more** than the loop operation. Out of those, all operations that are indented by exactly **one more space than the loop operation** are contained by this loop.
	* A module invocation in the form of `(modulename)`.
