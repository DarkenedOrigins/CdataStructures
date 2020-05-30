#include "shape.hpp"
double max(double a, double b){
	if(b > a){
		return b;
	}else{
		return a;
	}
}
//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name){
  name_ = name;
}
string Shape::getName(){return name_;}
//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width, double length): Shape("Rectangle"){
    width_ = width;
    length_ = length;
}
double Rectangle::getArea(){return width_*length_;}
double Rectangle::getVolume(){return 0.0;}

double Rectangle::getWidth(){return width_;}
double Rectangle::getLength(){return length_;}
Rectangle Rectangle::operator + (const Rectangle& rec){
	Rectangle R3(rec.width_+width_,rec.length_+length_);
	return R3;
}
Rectangle Rectangle::operator - (const Rectangle& rec){
	double a,b;
	a= width_-rec.width_;
	b= length_-rec.length_;
	a = max(0,a);
	b = max(0,b);
	Rectangle R3(a,b);
	return R3;
}
//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius): Shape("Circle"){
    radius_ = radius;
}

double Circle::getRadius(){return radius_;}
double Circle::getArea(){return M_PI*radius_*radius_;}
double Circle::getVolume(){return 0.0;}
Circle Circle::operator+( const Circle& cir){
	Circle C3( radius_+cir.radius_ );
	return C3;
}
Circle Circle::operator-(const Circle& cir){
	Circle C3(max(0,radius_-cir.radius_) );
	return C3;
}
//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius): Shape("Sphere"){
    radius_ = radius;
}

double Sphere::getRadius(){return radius_;}
double Sphere::getArea(){return 4.0*radius_*radius_*3.14159;}
double Sphere::getVolume(){return 4.0/3.0*radius_*radius_*radius_*3.14159;}
Sphere Sphere::operator + (const Sphere& sph){
	Sphere S3(radius_+sph.radius_);
	return S3;
}
Sphere Sphere::operator - (const Sphere& sph){
	Sphere S3( max(0,radius_-sph.radius_) );
	return S3;
}
//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height): Shape("RectPrism"){
    width_ = width;
    length_ = length;
    height_ = height;
}
double RectPrism::getWidth(){return width_;}
double RectPrism::getHeight(){return height_;}
double RectPrism::getLength(){return length_;}
double RectPrism::getArea(){return 2.0*(length_*width_ + length_*height_ + height_*width_);}
double RectPrism::getVolume(){return length_*width_*height_;}
RectPrism RectPrism::operator + (const RectPrism& rectp){
	RectPrism Rect(width_+rectp.width_,length_+rectp.length_,height_+rectp.height_);
	return Rect;
}
RectPrism RectPrism::operator - (const RectPrism& rectp){
	double a,b,c;
	a=max(0,width_-rectp.width_);
	b=max(0,length_-rectp.length_);
	c=max(0,height_-rectp.height_);
	RectPrism R(a,b,c);
	return R;
}
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
  int lines;
  double a, b, c;
  string data;
  Shape* shape_ptr;
  vector<Shape*> vs;
  ifstream infile;
  infile.open(file_name);
  infile >> lines;
  for (int i=0; i<lines; i++){
      infile >> data;
      // cout << data <<endl;
      if (data == "Circle"){
          // cout << "circle" << endl;
          infile >> a;
          shape_ptr = new Circle(a);
      }
      else if (data == "Rectangle"){
          // cout << "rectangle" << endl;
          infile >> a;
          infile >> b;
          shape_ptr = new Rectangle(a, b);
      }
      else if (data == "Sphere"){
          // cout << "sphere" << endl;
          infile >> a;
          shape_ptr = new Sphere(a);
      }
      else if (data == "RectPrism"){
          // cout << "prism" << endl;
          infile >> a;
          infile >> b;
          infile >> c;
          shape_ptr = new RectPrism(a, b, c);
      }
      vs.push_back(shape_ptr);
  }

  infile.close();
  if (vs.size() != lines){
      // Quick check to make sure we got everything
      return vector<Shape*>(0, NULL);
  } else {
      return vs;
  }
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  for (int i=0; i < shapes.size(); i++){
      if (shapes[i]->getArea() > max_area){
        max_area = shapes[i]->getArea();
      }
  }
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  for (int i=0; i < shapes.size(); i++){
      if (shapes[i]->getVolume() > max_volume){
        max_volume = shapes[i]->getVolume();
      }
  }
	return max_volume;
}
