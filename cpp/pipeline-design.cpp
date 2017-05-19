/*
We are working on a batch image processing pipeline. We want to be able to list
the operations to be applied on all the images (and their parameters) in a
config file. For example:

ConvertToGrayScale
Blur 3.
Resize 256 256
Compress 9

The idea is to load the config file, create the pipeline, and process all the
images through the pipeline. We have access to a library for image manipulation
that has all the functions that we need for those operations.

How would you design such a pipeline?
This is intentionally vague, so part of the exercise is to define the scope.
Keep in mind that you have 30 minutes, so you are encouraged to first go for
a decently simple solution, and then discuss extensions.

In this case we will mock the behavior because we don't have IO, so basically
it should print:

one: Converting to gray scale
one: Blurring with factor 3
one: Resizing img with x = 256 and y = 256
one: Compressing img with factor 9
two: Converting to gray scale
two: Blurring with factor 3
two: Resizing img with x = 256 and y = 256
two: Compressing img with factor 9
three: Converting to gray scale
three: Blurring with factor 3
three: Resizing img with x = 256 and y = 256
three: Compressing img with factor 9
*/

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Mock image class
class Image {
public:
  Image (const string& name) : name_(name) {}
  const string& name() const { return name_; }
private:
  const string name_;
};


// Sample image manipulation library.
namespace ImgLib {

void convertToGrayScale (Image & img) {
  cout << img.name() << ": Converting to gray scale" << endl;
}

void blur (Image & img, float factor) {
  cout << img.name() << ": Blurring with factor " << factor << endl;
}

void resize (Image & img, int x, int y) {
  cout << img.name() << ": Resizing img with x = " << x << " and y = " << y << endl;
}

void compress (Image & img, int factor) {
  cout << img.name() << ": Compressing img with factor " << factor << endl;
}

/* Potentially many more! */

} // namespace ImgLib



// Note: Passing string& param in the operator call
// For example - if we have two Compress command in the pipeline with values 20 & 30
// How would we correctly instantiate same object with two different values and store that in the mapping
class Process {
  public:
	Process() {}
  	virtual void operator() (Image &img, string &param)  = 0;
  private:
};

class Blur : public Process {
public:
	Blur() {}
	void operator() (Image &img, string &param) override {
		stringstream ss(param);
		ss >> val;
		ImgLib::blur(img, val);
	}

  private:
    float val;
};

class ConvertToGrayScale : public Process {
public:
	ConvertToGrayScale() {}
	void operator() (Image &img, string &param) override {
		ImgLib::convertToGrayScale(img);
	}

  private:
};

class Resize : public Process {
public:
	Resize() {}
	void operator() (Image &img, string &param) override {
		stringstream ss(param);
		ss >> val1;
		ss >> val2;
		ImgLib::resize(img, val1, val2);
	}
private:
	int val1, val2;
};

class Compress : public Process {
public:
	Compress() {}
	void operator() (Image &img, string &param) override {
		printf("current val %d \n", val);
		stringstream ss(param);
		ss >> val;
		ImgLib::compress(img, val);
	}
private:
	int val;
};




std::map<std::string, Process *> mapping;


int main() {
    
	mapping["ConvertToGrayScale"] = new ConvertToGrayScale;
    mapping["Blur"] = new Blur;
    mapping["Resize"] = new Resize;
	mapping["Compress"] = new Compress;

     // Read the config file
  vector<string> cmds = {"ConvertToGrayScale",
                         "Blur 3.",
                         "Resize 256 256",
                         "Compress 29", // XXX: Added new compress config. See Note above
                         "Compress 9"};

  vector<Image> imgs = {Image ("one"),
                        Image ("two"),
                        Image ("three") };
    
    
	for (auto &img : imgs) { 

		for (auto &cmd : cmds) {

			stringstream ss(cmd);
			string token, args;
			ss >> token;
			getline(ss, args);

			if (auto it = mapping.find(token) != mapping.end()) {
				Process *p = mapping[token];
				(*p)(img, args);
			}
		}

	}
    
  return 0;
}
