#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

// TODO Write this function
int energy(const Pixel *const*image, int col, int row, int width, int height)
{
  int redX=0;
  int greenX=0;
  int blueX=0;
  int redY=0;
  int greenY=0;
  int blueY=0;
  if (width==1) {
  }
  else if (col == 0) {
    redX = abs(image[col+1][row].r - image[width-1][row].r);
    greenX = abs(image[col+1][row].g - image[width-1][row].g);
    blueX = abs(image[col+1][row].b - image[width-1][row].b);
  }
  else if (col == width - 1) {
    redX = abs(image[0][row].r - image[col-1][row].r);
    greenX = abs(image[0][row].g - image[col-1][row].g);
    blueX = abs(image[0][row].b - image[col-1][row].b);
  }
  else {
    redX = abs(image[col+1][row].r - image[col-1][row].r);
    greenX = abs(image[col+1][row].g - image[col-1][row].g);
    blueX = abs(image[col+1][row].b - image[col-1][row].b);
  }
  
  if (height==1) {
  }
  else if (row == 0) {
    redY = abs(image[col][row+1].r - image[col][height-1].r);
    greenY = abs(image[col][row+1].g - image[col][height-1].g);
    blueY = abs(image[col][row+1].b - image[col][height-1].b);
  }
  else if (row == height - 1) {
    redY = abs(image[col][0].r - image[col][row-1].r);
    greenY = abs(image[col][0].g - image[col][row-1].g);
    blueY = abs(image[col][0].b - image[col][row-1].b);
  }
  else {
    redY = abs(image[col][row+1].r - image[col][row-1].r);
    greenY = abs(image[col][row+1].g - image[col][row-1].g);
    blueY = abs(image[col][row+1].b - image[col][row-1].b);
  }
  
  int gradX = redX*redX + greenX*greenX + blueX*blueX;
  int gradY = redY*redY + greenY*greenY + blueY*blueY;
  int total = gradX + gradY;
  return total;
}

// TODO Write this function
int getVerticalSeam(const Pixel *const*image, int start_col, int width, int height, int* seam)
{
  int colDown;
  int colLeft;
  int colRight;
  seam[0] = start_col;
  int totEnergy = energy(image, start_col, 0, width, height);
  if (height==1) {
    return totEnergy;
  }
  for (int row = 1; row < height; row++) {
    if (width==1) {
      colDown = seam[row - 1];
      colLeft = colDown;
      colRight = colDown;
    }
    else if (seam[row - 1] == 0) { //if left most column
      colDown = seam[row - 1];
      colLeft = seam[row - 1] + 1; 
      colRight = colDown;
    }
    else if (seam[row - 1] == width - 1) { //if right most column
      colDown = seam[row - 1];
      colRight = seam[row - 1] - 1;
      colLeft = colDown;
    }
    else { //everything in middle
      colDown = seam[row - 1];
      colLeft = seam[row - 1] + 1;
      colRight = seam[row - 1] - 1; 
    } 
    if ((energy(image, colDown, row, width, height) <= energy(image, colLeft, row, width, height)) && (energy(image, colDown, row, width, height) <= energy(image, colRight, row, width, height))) { //if down is smallest
      seam[row] = colDown;
      totEnergy += energy(image, colDown, row, width, height);
    }
    else if ((energy(image, colLeft, row, width, height) <= energy(image, colRight, row, width, height)) && (energy(image, colLeft, row, width, height) <= energy(image, colDown, row, width, height))) { //if left is smallest
      seam[row] = colLeft;
      totEnergy += energy(image, colLeft, row, width, height);
    }
    else { //if right is smallest
      seam[row] = colRight;
      totEnergy += energy(image, colRight, row, width, height);
    }
  }
  return totEnergy;
}

// TODO Write this function
void removeVerticalSeam(Pixel **image, int& width, int height, int *verticalSeam)
{
  for (int row = 0; row < height; row++) {
    for (int col = verticalSeam[row]; col < width-1; col++)
      image[col][row] = image[col + 1][row];
  }
  width --;
}

// TODO Write this function for extra credit
int getHorizontalSeam(const Pixel *const*image, int start_row, int width, int height, int* seam)
{
  int rowForward;
  int rowLeft;
  int rowRight;
  seam[0] = start_row;
  int totEnergy = energy(image, 0, start_row, width, height);
  if (width==1) {
    return totEnergy;
  }
  for (int col = 1; col < width; col++) {
    if (height==1) {
      rowForward = seam[col - 1];
      rowLeft = rowForward;
      rowRight = rowForward;
    }
    else if (seam[col - 1] == 0) { //if top most row
      rowForward = seam[col - 1];
      rowRight = seam[col - 1] + 1; 
      rowLeft = rowForward;
    }
    else if (seam[col - 1] == height - 1) { //if bottom most row
      rowForward = seam[col - 1];
      rowLeft = seam[col - 1] - 1;
      rowRight = rowForward;
    }
    else { //everything in middle
      rowForward = seam[col - 1];
      rowRight = seam[col - 1] + 1;
      rowLeft = seam[col - 1] - 1; 
    } 
    if ((energy(image, col, rowForward, width, height) <= energy(image, col, rowLeft, width, height)) && (energy(image, col, rowForward, width, height) <= energy(image, col, rowRight, width, height))) { //ifwForward is smallest
      seam[col] = rowForward;
      totEnergy += energy(image, col, rowForward, width, height);
    }
    else if ((energy(image, col, rowLeft, width, height) <= energy(image, col, rowRight, width, height)) && (energy(image, col, rowLeft, width, height) <= energy(image, col, rowForward, width, height))) { //if left is smallest
      seam[col] = rowLeft;
      totEnergy += energy(image, col, rowLeft, width, height);
    }
    else { //if right is smallest
      seam[col] = rowRight;
      totEnergy += energy(image, col, rowRight, width, height);
    }
  }
  return totEnergy;
}

// TODO Write this function for extra credit
void removeHorizontalSeam(Pixel **image, int width, int& height, int *horizontalSeam)
{
  for (int col = 0; col < width; col++) {
    for (int row = horizontalSeam[col]; row < height-1; row++)
      image[col][row] = image[col][row + 1];
  }
  height --;
}

int *findMinVerticalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up 
  delete [] candidateSeam;

  return minSeam;
}

int *findMinHorizontalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first row (index 0)
  int *minSeam = new int[width]{0};
  int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[width]{0};
  int candidateDistance = -1; // invalid distance

  // start at second row (index 1) since we initialized with first row (index 0)
  for (int row = 1; row < height; ++row)
  {
    candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

    if (candidateDistance < minDistance)
    { // new minimum
      //  swap min and candidate seams
      minDistance = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

    // clean up 
  delete [] candidateSeam;

  return minSeam;
}

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel ** loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}