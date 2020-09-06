This is a example project for the S4ModApi. The goal of the Lua Example Plugin is to demonstrate how a plugin can interact with the games lua virtual machine by adding and calling lua functions. The plugin will add two blue buttons to the game. 

![luaexample](C:\Users\WIN10\source\repos\github\S4ModApi\Examples\LuaExample\luaexample.png)

When clicking the **Reveal World Map** button the lua example plugin will call the [ISettlers4Api::RevealWorldMap](https://github.com/nyfrk/S4ModApi/wiki/RevealWorldMap) method. This method will call the [Tutorial.RWM](https://s4.muffinmar.io/scripts/?id=Tutorial_RWM#Tutorial_RWM) lua function to reveal the map. Furthermore the plugin displays a text message in the notification box using [ISettlers4Api::ShowTextMessage](https://github.com/nyfrk/S4ModApi/wiki/ShowTextMessage). 

When clicking the **Call Ext.ShowMessage** button the lua example plugin will call the Ext.ShowMessage lua function. The plugin will add this lua function to the games lua virtual machine by using a Lua Open Hook that is provided by the S4ModApi. The Ext.ShowMessage function uses the S4ModApi to display a message using [ISettlers4Api::ShowTextMessage](https://github.com/nyfrk/S4ModApi/wiki/ShowTextMessage) method. This demonstrates how you can add custom lua functions to the games lua virtual machine and how you can call lua functions from a plugin.

# License

The Lua Example Plugin is licensed under the MIT license.