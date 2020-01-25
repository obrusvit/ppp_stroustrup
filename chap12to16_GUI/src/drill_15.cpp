#include "std_lib_facilities.h"
#include "Window.h"
#include "Graph.h"

double one(double) {return 1;}
double slope(double x) {return x/2;}
double square(double x) {return x*x;}
double sloping_cos(double x) {return cos(x)+slope(x);}
int main(){
    try {
        using namespace Graph_lib; 

        // Window
        constexpr int X_SIZE = 600;
        constexpr int Y_SIZE = 600;
        const string title = "Function graphs";
        Graph_lib::Window win{X_SIZE, Y_SIZE, title}; 

        // Axis
        const Point X_BEGIN{100, 300};
        const Point Y_BEGIN{300, 500};
        constexpr int X_AXIS_LEN = 400;
        constexpr int Y_AXIS_LEN = 400;
        constexpr int GAP_NOTCHES = 20; 
        const string X_AXIS_LAB = "1 == 20 pixels";

        Axis x_axis{Graph_lib::Axis::Orientation::x, X_BEGIN, X_AXIS_LEN, X_AXIS_LEN/GAP_NOTCHES, X_AXIS_LAB};
        Axis y_axis{Graph_lib::Axis::Orientation::y, Y_BEGIN, Y_AXIS_LEN, Y_AXIS_LEN/GAP_NOTCHES};
        x_axis.set_color(Graph_lib::Color::red);
        y_axis.set_color(Graph_lib::Color::red);

        win.attach(x_axis);
        win.attach(y_axis);
        
        // Functions
        // Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
        const Point ORIG{300, 300};
        constexpr int X_SCALE = 20;
        constexpr int Y_SCALE = 20;
        constexpr int R_MIN = -10;
        constexpr int R_MAX = 11;
        constexpr int NUM_POINTS = 400;

        Function f_one{one, R_MIN, R_MAX, ORIG, NUM_POINTS, X_SCALE, Y_SCALE};
        Function f_slope{slope, R_MIN, R_MAX, ORIG, NUM_POINTS, X_SCALE, Y_SCALE};
        Text f_slope_lab{Point{100, 380}, "x/2"};
        Function f_square{square, R_MIN, R_MAX, ORIG, NUM_POINTS, X_SCALE, Y_SCALE};
        Function f_cos{cos, R_MIN, R_MAX, ORIG, NUM_POINTS, X_SCALE, Y_SCALE};
        f_cos.set_color(Graph_lib::Color::blue);
        Function f_sloping_cos{sloping_cos, R_MIN, R_MAX, ORIG, NUM_POINTS, X_SCALE, Y_SCALE};
        

        win.attach(f_one);
        win.attach(f_slope);
        win.attach(f_slope_lab);
        win.attach(f_square);
        win.attach(f_cos);
        win.attach(f_sloping_cos);
        

        


        gui_main();
        return 0;
    }
    catch(exception& e){
        cerr << e.what() << "\n";
        return 1;
    }
    catch(...){
        cerr << "something went wrong\n";
        return 2;
    }
}
