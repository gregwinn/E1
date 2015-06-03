#include <TVout.h>
#include <fontALL.h>

TVout TV;

int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = 64;
float angle = PI/60;
void setup() {
  TV.begin(NTSC,128,104);
  TV.select_font(font4x6);
  TV.println("This is a 4x6 font test");
}

void loop() {
  // put your main code here, to run repeatedly:

}