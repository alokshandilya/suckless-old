// See LICENSE file for copyright and license details.
//
//              Patched by - Alok Shandilya
//
//    ▄▀█ █░░ █▀█ █▄▀   █▀ █░█ ▄▀█ █▄░█ █▀▄ █ █░░ █▄█ ▄▀█
//    █▀█ █▄▄ █▄█ █░█   ▄█ █▀█ █▀█ █░▀█ █▄▀ █ █▄▄ ░█░ █▀█
//
//

#include <X11/XF86keysym.h>

/* Constants : Using preprocessor */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "brave"
#define BROWSERCLASS "Brave-browser"

// appearance
static const unsigned int borderpx          = 2;        // border pixel of windows
static const unsigned int snap              = 32;       // snap pixel
static const unsigned int systraypinning    = 0;   		// 0: sloppy systray follows selected monitor, >0: pin systray to monitor X
static const unsigned int systrayonleft     = 0;   		// 0: systray in the right corner, >0: systray on left of status text
static const unsigned int systrayspacing    = 2;   		// systray spacing
static const int systraypinningfailfirst    = 1;   		// 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor
static const int showsystray                = 1;     	// 0 means no systray
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar                    = 1;        // 0 means no bar
static const int topbar                     = 1;        // 0 means bottom bar


// *fonts [FiraCode Nerd Font, JetBrainsMono Nerd Font]
static const char *fonts[]     		= { "FiraCode Nerd Font:style:bold:size=10", "FontAwesome:size=11",
                                  		"Twemoji:size=11:antialias=true:autohint=true"};

static const char dmenufont[]       =  "FiraCode Nerd Font:style:bold:size=11";
										// "Hack:size=11:antialias=true:autohint=true",
										// "JoyPixels:size=11:antialias=true:autohint=true"


// nord colorscheme
// static const char col_gray1[]       = "#2E3440";
// static const char col_gray2[]       = "#2E3440";
// static const char col_gray3[]       = "#D8DEE9";
// static const char col_gray4[]       = "#2E3440";
// static const char col_border[]      = "#46d9ff";
// static const char col_cyan[]        = "#8FBCBB";	// used for dmenu too
// static const char col_midbar[]		= "#2E3440";
// static const char col_titletext[]	= "#5E81AC";

// solarized colorscheme
//static const char col_gray1[]       = "#002A36";
/* static const char col_gray1[]       = "#002732"; */
/* static const char col_gray2[]       = "#0D3642"; */
/* static const char col_gray3[]       = "#EEE8D5"; */
/* static const char col_gray4[]       = "#0D3642"; */
/* static const char col_border[]      = "#46d9ff"; */
/* static const char col_cyan[]        = "#2AA198";	// used for dmenu too */
/* static const char col_midbar[]		= "#0D3642"; */
/* static const char col_titletext[]	= "#2AA198"; */

// one dark colorscheme
// static const char col_gray1[]       = "#1e222a";
// static const char col_gray2[]       = "#444444";
// static const char col_gray3[]       = "#E4E4E4";
// static const char col_gray4[]       = "#282c34";
// static const char col_border[]      = "#61afef";
// static const char col_cyan[]        = "#61afef";	// used for dmenu too
// static const char col_midbar[]		= "#61afef";

// gruvbox colorscheme
// static const char col_gray1[]       = "#1d2021";
// static const char col_gray2[]       = "#504945";
// static const char col_gray3[]       = "#ebdbb2";
// static const char col_gray4[]       = "#1d2021";
// static const char col_border[]      = "#46d9ff";
// static const char col_cyan[]        = "#458588";	// used for dmenu too
// static const char col_midbar[]		= "#1d2021";
// static const char col_titletext[]	= "#458588";

// gruvbox-material colorscheme
static const char col_gray1[]       = "#1d2021";
static const char col_gray2[]       = "#504945";
static const char col_gray3[]       = "#D3BD97";
static const char col_gray4[]       = "#1d2021";
static const char col_border[]      = "#46d9ff";
static const char col_cyan[]        = "#EA6962";	// used for dmenu too
static const char col_midbar[]		= "#1d2021";
static const char col_titletext[]	= "#E6894E";

// tomorrow-night colorscheme
// static const char col_gray1[]       = "#1d1f21";
// static const char col_gray2[]       = "#373b41";
// static const char col_gray3[]       = "#c5c8c6";
// static const char col_gray4[]       = "#1d1f21";
// static const char col_border[]      = "#8be9fd";
// static const char col_cyan[]        = "#cc6666";	// used for dmenu too
// static const char col_midbar[]		= "#1d1f21";
// static const char col_titletext[]	= "#de935f";

// dracula colorscheme
/* static const char col_gray1[]       = "#282a36"; */
/* static const char col_gray2[]       = "#44475a"; */
/* static const char col_gray3[]       = "#f8f8f2"; */
/* static const char col_gray4[]       = "#282a36"; */
/* static const char col_border[]      = "#8be9fd"; */
/* static const char col_cyan[]        = "#bd93f9";	// used for dmenu too */
/* static const char col_midbar[]		= "#282a36"; */
/* static const char col_titletext[]	= "#bd93f9"; */

static const char *colors[][3] = {
	/*               fg					bg				border  */
	[SchemeNorm]	= { col_gray3,		col_gray1,		col_gray2 },
	[SchemeSel]		= { col_gray4,		col_cyan,		col_border },
	[SchemeTitle]	= { col_titletext,	col_midbar,		col_cyan  },
};

static const char *const autostart[] = {
    "sh", "-c", "/usr/bin/emacs --daemon", NULL,
    "./.fehbg", NULL,
    "sh", "-c", "picom --config ~/.config/picom/picom.conf --experimental-backends", NULL,
    "lxsession", NULL,
    "dunst", NULL,
    "xbanish", NULL,
    "numlockx", "on", NULL,
    "sh", "-c", "conky -c ~/.config/conky/gruvbox-material.conkyrc", NULL,
    "sh", "-c", "~/Documents/GitHub/suckless/dwmblocks/dwmblocks", NULL,
    NULL /* terminate */
};

// tagging
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "", "", "", "", "", "嗢", "", "", ""};
// static const char *tags[] = { "", " ", "", "", "", "", "", "", ""};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

// tagsel colors [nord]
// static const char *tagsel[][2] = {
//     { "#2E3440", "#5E81AC" },
//     { "#2E3440", "#BF616A" },
//     { "#2E3440", "#EBCB8B" },
//     { "#2E3440", "#A3BE8C" },
//     { "#2E3440", "#B48EAD" },
//     { "#2E3440", "#D08770" },
//     { "#2E3440", "#5E81AC" },
//     { "#D8DEE9", "#BF616A" },
//     { "#2E3440", "#A3BE8C" },
// };

// tagsel colors [solarized]
// static const char *tagsel[][2] = {
//     { "#002b36", "#2AA198" },
//     { "#002b36", "#268BD2" },
//     { "#EEE8D5", "#B58900" },
//     { "#002b36", "#859900" },
//     { "#002b36", "#6C71C4" },
//     { "#002b36", "#CB4B16" },
//     { "#002b36", "#859900" },
//     { "#EEE8D5", "#DC322F" },
//     { "#002b36", "#2AA198" },
// };

// tagsel colors [gruvbox]
static const char *tagsel[][2] = {
	{ "#EA6962", "#1d2021" },
	{ "#A8B565", "#1d2021" },
	{ "#d3869b", "#1d2021" },
	{ "#7daea3", "#1d2021" },
	{ "#fbf1c7", "#1d2021" },
	{ "#e6894e", "#1d2021" },
	{ "#7daea3", "#1d2021" },
	{ "#fbf1c7", "#1d2021" },
	{ "#e6894e", "#1d2021" },
};

// tagsel colors [dracula]
// static const char *tagsel[][2] = {
//     { "#282a36", "#ff79c6" },
//     { "#282a36", "#6272a4" },
//     { "#282a36", "#50fa7b" },
//     { "#282a36", "#bd93f9" },
//     { "#fbf1c7", "#ff5555" },
//     { "#282a36", "#bd93f9" },
//     { "#282a36", "#50fa7b" },
//     { "#282a36", "#ff79c6" },
//     { "#282a36", "#ffb86c" },
// };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     		 	 instance    title       tags mask     switchtotag      isfloating   monitor */
	{ "Gimp",                NULL,       NULL,       1 << 5,       1,               0,           0 },
	{ "vlc",                 NULL,       NULL,       1 << 5,       1,               0,           0 },
	{ "mpv",                 NULL,       NULL,       1 << 5,       1,               0,           0 },
	{ "firefox",             NULL,       NULL,       1 << 0,       1,               0,           0 },
	{ BROWSERCLASS,          NULL,       NULL,       1 << 0,       1,               0,           0 },
	{ "Code",                NULL, 	     NULL,		 1 << 1,       1,	            0,           0 },
	{ "jetbrains-idea-ce",   NULL,	     NULL,       1 << 1,       1,  	            0,           0 },
	{ "Emacs",               NULL,	     NULL,       1 << 1,       1,  	            0,           0 },
	/* { TERMCLASS,             NULL,       NULL,       1 << 1,       1,  	            0,           0 }, */
	{ "GitHub Desktop",      NULL,       NULL,       1 << 2,       1,               0,           0 },
	{ "Rhythmbox",           NULL,       NULL,       1 << 3,       1,               0,           0 },
	{ "Mailspring",          NULL,       NULL,       1 << 6,       1,               0,           0 },
	{ "TelegramDesktop",     NULL,       NULL,       1 << 6,       1,               0,           0 },
	{ "Soffice",             NULL,       NULL,       1 << 4,       1,               0,           0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{0, MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{0, MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{0, MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{0, MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/dash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", NULL };

static const char *termcmd[]  = { TERMINAL, NULL };
static const char scratchpadname[] = "Alok's Playing Area-51 🏏";
static const char *scratchpadcmd[] = { TERMINAL, "-t", scratchpadname, "-g", "135x34", NULL };

static const char *mutecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
//static const char *miccmd[] = { "amixer", "set", "Capture", "toggle", NULL };

static const char *brupcmd[] = { "brightnessctl", "s", "1%+", NULL };
static const char *brdowncmd[] = { "brightnessctl", "s", "1%-", NULL };

static const char *browsercmd[] = { "./.config/scripts/brave-launcher", NULL };
static const char *filemanagercmd[] = { "/usr/bin/thunar", NULL };
// static const char *filemanagercmd[] = { "/usr/bin/pcmanfm", NULL };
//static const char *filemanagercmd[] = { "/usr/bin/dolphin", NULL };
static const char *codecmd[] = { "/usr/bin/code", NULL };
//static const char *plannercmd[] = { "/usr/bin/planner", NULL };
static const char *volume_control[] = { "/usr/bin/pavucontrol", NULL };
//static const char *email_client[] = { "/usr/bin/mailspring", NULL };
static const char *ranger[] = { TERMINAL, "-e", "ranger", NULL };
static const char *nvimcmd[] = { TERMINAL, "-e", "nvim", NULL };

//static const char *googletasks[] = { "/usr/lib/brave-bin/brave", "--profile-directory=Default", "--app-id=ffpdhnednbmelagcknnegjemgooenfml", NULL };
static const char *bpytop[] = { TERMINAL, "-e", "bpytop", NULL };

static const char *printscr_full[] = { "spectacle", NULL };
static const char *printscr[] = { "/home/aloks/.config/scripts/printscr", NULL };
static const char *lockscreen[] = { "betterlockscreen", "-l", "blur", NULL };
static const char *poweroffcmd[] = { "poweroff", NULL };
static const char *rebootcmd[] =  { "systemctl", "reboot", NULL };

#define MULTIKEY_THRESHOLD_MS_PRESS 200
#define MULTIKEY_THRESHOLD_MS_HOLD 700

#include "movestack.c"
static Key keys[] = {
	/* npressed,	modifier                    key        function        argument */
	{ 2,			MODKEY,                     XK_d,      spawn,         {.v = dmenucmd } },
	{ 1,			MODKEY,		                XK_Return, spawn,         {.v = termcmd } },
	{ 0,      		MODKEY,                     XK_grave,  togglescratch, {.v = scratchpadcmd } },
	{ 1,			MODKEY,						XK_d,	   spawn,	      {.v = roficmd } },
	{ 1,			MODKEY,						XK_w,	   spawn,	      {.v = browsercmd } },
	{ 1,			MODKEY,						XK_e,	   spawn,	      {.v = filemanagercmd } },
	{ 1,			MODKEY,						XK_v,	   spawn,	      {.v = codecmd } },
	/* { 0,			MODKEY,						XK_n,	   spawn,	      {.v = plannercmd } }, */
	/* { 0,			MODKEY,						XK_n,	   spawn,	      {.v = googletasks } }, */

	{ 0,			MODKEY|ShiftMask,			XK_d,	   spawn,	   SHCMD("emacsclient -c -a 'emacs' --eval '(dashboard-refresh-buffer)'") },
	{ 1,			MODKEY|ShiftMask,			XK_d,	   spawn,	   {.v = nvimcmd } },
	{ 2,			MODKEY,						XK_v,	   spawn,	   {.v = volume_control } },
	{ 2,			MODKEY,						XK_e,	   spawn,	   {.v = ranger } },
	{ 0,			MODKEY|ShiftMask,			XK_t,	   spawn,	   {.v = bpytop } },
	{ 1,			MODKEY,						XK_s,	   spawn,	   SHCMD("env LD_PRELOAD=/usr/lib/spotify-adblock.so spotify %U") },
	//{ 0,			MODKEY|ShiftMask,			XK_m,	   spawn,	   {.v = email_client } },
	{ 2,			MODKEY,						XK_s,	   spawn,	   {.v = lockscreen } },

	{ 0,			MODKEY,                     XK_b,      togglebar,      {0} },
	{ 0,			MODKEY,                     XK_j,      focusstack,     {.i = +1 } },
	{ 0,			MODKEY,                     XK_k,      focusstack,     {.i = -1 } },
	{ 0,			MODKEY,                     XK_i,      incnmaster,     {.i = +1 } },
	{ 0,			MODKEY,                     XK_o,      incnmaster,     {.i = -1 } },
	{ 0,			MODKEY,                     XK_h,      setmfact,       {.f = -0.05} },
	{ 0,			MODKEY,                     XK_l,      setmfact,       {.f = +0.05} },
	{ 0,			MODKEY|ShiftMask,           XK_h,      setcfact,       {.f = +0.25} },
	{ 0,			MODKEY|ShiftMask,           XK_l,      setcfact,       {.f = -0.25} },
	{ 0,			MODKEY|ShiftMask,           XK_o,      setcfact,       {.f =  0.00} },
	{ 0,			MODKEY|ShiftMask,           XK_j,      movestack,      {.i = +1 } },
	{ 0,			MODKEY|ShiftMask,           XK_k,      movestack,      {.i = -1 } },
	{ 0,			MODKEY|ShiftMask,           XK_Return, zoom,           {0} },

	{ 0, MODKEY|ControlMask,              XK_u,      incrgaps,       {.i = +1 } },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ 0, MODKEY|ControlMask,              XK_i,      incrigaps,      {.i = +1 } },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ 0, MODKEY|ControlMask,              XK_o,      incrogaps,      {.i = +1 } },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ 0, MODKEY|ControlMask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ 0, MODKEY|ControlMask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ 0, MODKEY|ControlMask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ 0, MODKEY|ControlMask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ 0, MODKEY|ControlMask,              XK_0,      togglegaps,     {0} },
	{ 0, MODKEY|ControlMask|ShiftMask,    XK_0,      defaultgaps,    {0} },
        
	{ 0,			MODKEY,                     XK_Tab,    view,           {0} },
	{ 0,			MODKEY|ShiftMask,           XK_q,      killclient,     {0} },
	{ 0,			MODKEY,                     XK_t,      setlayout,      {.v = &layouts[0]} },
	{ 1,			MODKEY,                     XK_f,      setlayout,      {.v = &layouts[1]} },
	{ 0,			MODKEY,                     XK_m,      setlayout,      {.v = &layouts[2]} },
	{ 0,            MODKEY,                     XK_r,      setlayout,      {.v = &layouts[3]} },
	{ 0,            MODKEY|ShiftMask,           XK_r,      setlayout,      {.v = &layouts[4]} },
	{ 0,            MODKEY|ControlMask,         XK_comma,  cyclelayout,    {.i = -1 } },
	{ 0,            MODKEY|ControlMask,         XK_period, cyclelayout,    {.i = +1 } },
	{ 0,			MODKEY,                     XK_space,  setlayout,      {0} },
	{ 0,			MODKEY|ShiftMask,           XK_space,  togglefloating, {0} },
	{ 2,			MODKEY,			            XK_f,      togglefullscr,  {0} },

	{ 0,			MODKEY,                     XK_0,      view,           {.ui = ~0 } },
	{ 0,			MODKEY|ShiftMask,           XK_0,      tag,            {.ui = ~0 } },
	{ 0,			MODKEY,                     XK_comma,  focusmon,       {.i = -1 } },
	{ 0,			MODKEY,                     XK_period, focusmon,       {.i = +1 } },
	{ 0,			MODKEY|ShiftMask,           XK_comma,  tagmon,         {.i = -1 } },
	{ 0,			MODKEY|ShiftMask,           XK_period, tagmon,         {.i = +1 } },
	{ 1,			MODKEY|ControlMask,         XK_q,      quit,           {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ 0,	0,		XF86XK_AudioMute,			spawn,			{.v = mutecmd } },
	{ 0,	0,		XF86XK_AudioLowerVolume,	spawn,			{.v = voldowncmd } },
	{ 0,	0,		XF86XK_AudioRaiseVolume,	spawn,			{.v = volupcmd } },
	{ 0,	0,		XF86XK_MonBrightnessUp,		spawn,			{.v = brupcmd} },
	{ 0,	0,		XF86XK_MonBrightnessDown,	spawn,			{.v = brdowncmd} },

	// for keyboard with no media keys (some doen't even have function key...)
	{ 0,	MODKEY|ControlMask,		XK_h,		spawn,			{.v = voldowncmd } },
	{ 0,	MODKEY|ControlMask,		XK_l,		spawn,			{.v = volupcmd } },
	{ 0,	MODKEY|ControlMask,		XK_x,		spawn,			{.v = brupcmd} },
	{ 0,	MODKEY|ControlMask,		XK_z,		spawn,			{.v = brdowncmd } },

	{ 0,	MODKEY,					XK_F2,	   spawn,	   SHCMD("feh --bg-fill -zr ~/Documents/GitHub/wallpapers") },
	{ 0,	MODKEY,					XK_F1,	   spawn,	   SHCMD("~/.config/scripts/dmenu-scripts/./wallchange.sh") },
	{ 0,	0,						XK_Print,  spawn,	   {.v = printscr_full} },
	{ 0,	ShiftMask,				XK_Print,  spawn,	   {.v = printscr} },
	{ 2,	MODKEY|ControlMask,		XK_q,	   spawn,	   {.v = poweroffcmd} },
	{ 3,	MODKEY|ControlMask,		XK_q,	   spawn,	   {.v = rebootcmd} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
