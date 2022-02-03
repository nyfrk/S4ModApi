# S4ModApi Versioning

Every release gets from now on a fixed Application Binary Interface (ABI), meaning that mods linking against an older version will still be compatible even when a more recent S4ModApi.dll is used. The COM Pattern is used to ensure ABI compatibility. This allows players to update the S4ModApi.dll independently of their plugins. Plugins can be made compatible by updating S4ModApi.dll when new game versions are published - without having to recompile or even touching the source code of a plugin.



## Semantic Versioning

S4ModApi now adopts a semantic versioning scheme (mayor.minor.patch). The digits are increased according to the following rules.

* Mayor digit is increased when a new interface using a fresh UUID is added to the S4ModApi. The new interface may reorder, add, change or remove methods from the interface. Specification of methods may change. Interfaces requested using an older UUID will still get an appropriate interface.

* Minor digit is increased when specification changes happen that do not break previous versions interfaces and no new UUID is required. That is the case when methods are just appended to the current interface or when all methods still adhere mostly to their previous specification. For example a specification change is acceptable if a previously reserved argument or method is now implemented. This is also the case for bug fixes.

* Patch digit is not used and always 0. It is ignored by the auto update feature for now. 

Versions according to these rules may also be increased even for changes to older interfaces. Lets say for example the current S4ModApi is in version 3.3. The change to 3.4 may change features that were initially implemented in version 2.0 (e.g. bug fixes). Plugins that were linked to version 2.0 may now enjoy the fixed behavior even though it was linked against the older version. Please note that at some point this will be difficult to maintain and we may thus decide at any point to not fix old bugs. Especially when we notice that plugins rely on these. 

Note: If your plugin was compiled against version 1.x or older you will have to recompile your plugin using a newer S4ModApi Version. 



## ISettlers4Api Interface Versioning

With every mayor version a new interface is created. These are indicated by the suffix to the interface name. For example ISettlers4Api3 is the interface requested by plugins that were compiled using S4ModApi 3.x.x. When recompiling your plugin using the latest S4ModApi, make sure to replace the old S4ModApi.h header file and the linking library S4ModApi.lib. 

