#include <SPI.h>
#include <Gamebuino.h>

//Font variables

//-------------------------------------

Gamebuino gb;
extern const byte font5x7[];

//-------------------------------------
//Stuff from magpi
#define W LCDWIDTH
#define H LCDHEIGHT

#define PAD_U 0x01
#define PAD_D 0x02
#define PAD_L 0x04
#define PAD_R 0x08
#define PAD_A 0x10
#define PAD_B 0x20
#define PAD_C 0x40

byte px,py;
boolean pd;
byte p_state;

byte kc;

byte flash_color;

//-------------------------------------
//define images
const byte logo[] PROGMEM= {
  84, 48,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x7F,0x03,0xF8,0x01,0xC0,0xE3,0x03,0xF8,0x3F,0x80,0x00,
  0x08,0x80,0x44,0x02,0x20,0x31,0x00,0x80,0x04,0x40,0x00,
  0x08,0x80,0xF8,0x03,0xE0,0x15,0x00,0xF0,0x0F,0x80,0x00,
  0x08,0x80,0x44,0x02,0x20,0x1B,0x00,0x80,0x04,0x40,0x00,
  0x1F,0x00,0x44,0x1E,0x60,0x11,0x00,0xFF,0x04,0x40,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,
  0x0A,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,
  0x0D,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,
  0x0A,0xD0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,
  0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x84,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x8E,0x00,
  0x01,0x04,0x78,0x0E,0x00,0x00,0x00,0x08,0x08,0x95,0x00,
  0x02,0x8A,0x45,0x91,0x00,0x00,0x00,0x14,0xC8,0x84,0x00,
  0x04,0x44,0x45,0xA0,0x80,0x00,0x00,0x22,0xC8,0x84,0x00,
  0x04,0x4D,0x78,0x22,0xA0,0x00,0x00,0x22,0x0F,0x84,0x00,
  0x07,0xD6,0x45,0xA1,0xC0,0x00,0x00,0x3E,0xC7,0x04,0x00,
  0x04,0x52,0x45,0x90,0x80,0x00,0x00,0x22,0xC2,0x15,0x00,
  0x04,0x4D,0x78,0x0E,0x00,0x00,0x00,0x22,0x02,0x0E,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xC0,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x04,0x00,0x22,0x80,0x00,0x00,0x3C,0x00,0x00,0x00,
  0x01,0x0A,0x11,0xA2,0x40,0x00,0x00,0x22,0xDF,0xFE,0x00,
  0x02,0x04,0x09,0xA3,0xC0,0x00,0x00,0x22,0xD5,0xA0,0x00,
  0x07,0xCD,0x7C,0x20,0x40,0x00,0x00,0x3C,0x1A,0xA0,0x00,
  0x02,0x16,0x09,0xA0,0x40,0x00,0x00,0x22,0xD5,0xA0,0x00,
  0x01,0x12,0x11,0xA0,0x40,0x00,0x00,0x22,0xDF,0xFE,0x00,
  0x00,0x0D,0x00,0x20,0x40,0x00,0x00,0x3C,0x00,0x00,0x00,
  0x00,0x00,0x00,0x3F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
};

//------------------------------------------------------------------------------
//Canvas
byte canvas[530] = {
    84, 48
};

void paintPixel(byte x, byte y) {
	int b = 2 + (y * 11) + (x/8);
	canvas[b] |= 0x80 >> x%8;
}

void myDrawBitmap(byte x, byte y, byte *bitmap) {
	byte xb = *(bitmap++);
	byte yb = *(bitmap++);
	byte rows = yb;
	byte columns = xb/8 + ((xb%8) ? 1 : 0);
	byte row,column,b;
	for(row=0;row<rows;row++) {
		for(column=0;column<columns;column++) {
			for(b=0;b<8;b++) {
				if ((0x80 >> b) & *bitmap ) gb.display.drawPixel(column*8+b,row);
			}
			bitmap++;
		}
	}
}

//------------------------------------------------------------------------------
//Menus
////declare all the variables needed to make a menu

//number of items in the menu
#define MAINMENULENGTH 5
#define SETTINGSMENULENGTH 2
#define CONFIRMMENULENGTH 2

//The different strings to put in the menu
//each string can be used in different menus
const char strSettings[] PROGMEM = "Settings";
const char strClear[] PROGMEM = "Clear";
const char strSave[] PROGMEM = "Save";
const char strExport[] PROGMEM = "Export";
const char strQuit[] PROGMEM = "Quit";

//Confirm clear
const char strClearYes[] PROGMEM = "Yes, Clear";
const char strClearNo[] PROGMEM = "No, Cancel";

//Within settings
const char strPenSize[] PROGMEM = "Pen Size";
const char strEraserSize[] PROGMEM = "Eraser Size";


//Put all the different items together in a menu (an array of strings actually)
const char* const mainmenu[MAINMENULENGTH] PROGMEM = {
	strSettings,
	strClear,
	strSave,
  	strExport,
	strQuit,
};

const char* const settingsmenu[SETTINGSMENULENGTH] PROGMEM = {
	strPenSize,
	strEraserSize,
};

const char* const clearmenu[CONFIRMMENULENGTH] PROGMEM = {
	strClearYes,
	strClearNo,
};

void doMenus(){
	
	boolean done = false;
	
	while(!done){
		switch(gb.menu(mainmenu, MAINMENULENGTH)){
 				
 		  case 0: //Settings
 			
 		  	switch(gb.menu(settingsmenu, SETTINGSMENULENGTH)){
 					 					
 		    	  case 0: //Pen Size
 				  	//FIXME
				    done = true;
 		        	break;
 					
 		    	  case 1: //Eraser Size
 				  	//FIXME
			    	done = true;
 		        	break;

 		  	}
 		   	break;
 				
 		  case 1: //Clear
		  	switch(gb.menu(clearmenu, CONFIRMMENULENGTH)){
 			case 0: //doClear
 				//FIXME
		    	done = true;
 				break;
 				}
 			break;
 			case 2: //Save
 			   	//FIXME
				done = true;
 			    break;
 				
 			case 3: //Export
 			   	//FIXME
				done = true;
 			    break;
 				
 			case 4: //Quit
 				setup();
				done = true;
 			    break;
				
			default:
				done = true;
				break;
 			
 			}
 		}
}

//------------------------------------------------------------------------------
#define FRAMES_PER_SECOND 20

boolean any_button_pressed() {
	if(gb.buttons.pressed(BTN_A|BTN_B|BTN_C|BTN_LEFT|BTN_RIGHT|BTN_UP|BTN_DOWN)){
		return true;
	}
}

void doKC() {
	gb.backlight.automatic = false;
  	gb.backlight.set(0);
	delay(200);
	gb.backlight.set(255);
	delay(200);
  	gb.backlight.set(0);
  	delay(200);  
  	gb.backlight.set(255);
  	delay(200);
  	gb.backlight.set(0);
  	delay(200);
  	gb.backlight.set(255);
  	delay(200);
  	gb.backlight.set(0);
  	delay(200);
  	gb.backlight.set(255);
  	delay(200);
  	gb.backlight.set(0);
  	delay(200);
	gb.backlight.automatic = true;
}

//------------------------------------------------------------------------------
void setup()
{
    gb.begin();
    gb.display.setFont(font5x7);
    gb.titleScreen(F(""), logo);
	
	gb.display.persistence = true;
    gb.battery.show = true;
	gb.setFrameRate(20);
    gb.display.clear();
	
    gb.pickRandomSeed();
	
    kc = 0;
    px = W/2;
    py = H/2;
    pd = false;

    p_state = 0;
}

//------------------------------------------------------------------------------
void loop()
{
    if(gb.update()) {
		//------------------------------------------------------------------------------
		//void drawer():		
	    if (!pd){
	    	if(!(gb.frameCount % 5)) { // !(gb.frameCount % 10) means (gb.frameCount % 10 == 0)
		  	  flash_color = gb.display.getPixel(px,py) ? 0:1;
	    	}
			gb.display.setColor(flash_color);
	      	gb.display.drawPixel(px,py);
		}
		
      // <DO NOT TRY TO FIGURE OUT WHAT THIS CODE DOES!>
	  
      boolean done = 0;
      if(gb.buttons.pressed(BTN_UP) && ((kc == 0) || (kc == 1))) {
        kc++;
        done = 1;
      }
      if(gb.buttons.pressed(BTN_DOWN) && ((kc == 2) || (kc == 3))) {
        kc++;
        done = 1;
      }
      if(gb.buttons.pressed(BTN_LEFT) && ((kc == 4) || (kc == 6))) {
        kc++;
        done = 1;
      }
      if(gb.buttons.pressed(BTN_RIGHT) && ((kc == 5) || (kc == 7))) {
        kc++;
        done = 1;
      }
      if(gb.buttons.pressed(BTN_B) && (kc == 8)) {
        kc++; 
        done = 1;
      }
      if(gb.buttons.pressed(BTN_A) && (kc == 9)) {
        kc++;
        done = 1;
      }
      if(gb.buttons.pressed(BTN_C) && (kc == 10)) {
        kc++;
        done = 1;
      }
      if(done != 1) kc = 0;
      if(kc == 11) doKC();
      // </DO NOT TRY TO FIGURE OUT WHAT THIS CODE DOES!>

      if(!pd && (gb.buttons.pressed(BTN_DOWN) || gb.buttons.pressed(BTN_UP) || gb.buttons.pressed(BTN_LEFT) || gb.buttons.pressed(BTN_RIGHT))) {
		gb.display.setColor(p_state);		
        gb.display.drawPixel(px,py);
      }
	  
      if(gb.buttons.pressed(BTN_C)) {
		setup(); //reset
      }
      if(gb.buttons.pressed(BTN_LEFT)) {
      	if(px == 0) px=W-1; //move left
        else px--;
	  }
      if(gb.buttons.pressed(BTN_RIGHT)) {
        if(px == W-1) px=0; //move right
        else px++;
	  }
      if(gb.buttons.pressed(BTN_DOWN)) {
        if (py == H-1) py=0; //move down
        else py++;
	  }
      if(gb.buttons.pressed(BTN_UP)) {
        if(py == 0) py=H-1; //move up
        else py--;
	  }
      if(gb.buttons.pressed(BTN_A)) {
        pd = pd ? false : true; //toggle pen down
	  }
      if(gb.buttons.pressed(BTN_B)) {
        if(!pd) p_state = 0;
	  }
      if(!pd && (gb.buttons.pressed(BTN_DOWN) || gb.buttons.pressed(BTN_UP) || gb.buttons.pressed(BTN_LEFT) || gb.buttons.pressed(BTN_RIGHT))) {
        p_state = gb.display.getPixel(px,py);
      }
      if(pd) {
		gb.display.setColor(1);
   	   	gb.display.drawPixel(px,py);
  		if(gb.buttons.pressed(BTN_A)) p_state = 1;
      }
    }	
}