//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/	 	/*Update Interval*/	/*Update Signal*/
       	//{" 🐧 ", "$HOME/.config/scripts/kernel",		    360,		        2},

	{" ⛅ ", "/home/aloks/.config/scripts/weather.sh",		60,				1},

	{" 🔺 ", "$HOME/.config/scripts/upt",		        60,		            2},

	{" 📦 ", "$HOME/.config/scripts/pacupdate",		360,		        9},
	
	{" 💻 ", "$HOME/.config/scripts/memory",	        6,		            1},

	{" 🔋 ", "$HOME/.config/scripts/battery.sh",			150,			1},

	{" 🔊 ", "$HOME/.config/scripts/volume",			2,		            10},


	{" 🕑 ", "$HOME/.config/scripts/clock",			5,		            0},

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = '|';
