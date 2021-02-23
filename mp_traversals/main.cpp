
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  Animation animation;
  PNG baseImage;
  baseImage.readFromFile("image.png");
  FloodFilledImage image(baseImage);
  DFS* dfs1 = new DFS(baseImage, Point(200,200), 0.2);
  BFS* bfs2 = new BFS(baseImage, Point(205,205), 0.2);
  BFS* bfs3 = new BFS(baseImage, Point(210,210), 0.2);
  DFS* dfs = new DFS(baseImage, Point(400,0), 0.1);
  MyColorPicker color1(20, 200, Point(200,200));
  //MyColorPicker color2(100, 130, Point(205,205));
  //MyColorPicker color3(100, 90, Point(210, 210));
  //GradientColorPicker gcolor;
  RainbowColorPicker rcolor(10);
  //MyColorPicker color2(100, 150, Point400,1);
  image.addFloodFill(*dfs1, color1);
  //image.addFloodFill(*bfs2, color2);
  //image.addFloodFill(*bfs3, color3);
  image.addFloodFill(*dfs, rcolor);
  animation = image.animate(10000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
