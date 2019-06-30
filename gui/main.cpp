#include "std_lib_facilities.h"
#include "support_code/Simple_window.h"
#include "support_code/Graph.h"

int main(){
    try {
        //
        using namespace Graph_lib; 
        cout << "Starting...\n";
        Point tl {100, 100};
        Simple_window window{tl, 600, 400, "Win"};

        Polygon poly;
        poly.add(Point{300, 200});
        poly.add(Point{350, 100});
        poly.add(Point{400, 200});

        poly.set_color(Color::red);
        window.attach(poly);
	    //Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");
        Point zero{30, 300};
        Axis xa {Axis::Orientation::x, zero, 200, 10, "time"};
        Axis ya {Axis::Orientation::y, zero, 200, 10, "value"};
        window.attach(xa);
        window.attach(ya);

        Function sine{sin, 0, 100, zero, 1000, 50, 50};
        sine.set_color(Color::dark_red);
        window.attach(sine);

        Polygon poly_2;
        poly_2.add(Point{500, 100});
        poly_2.add(Point{300, 100});
        poly_2.add(Point{300, 200});
        poly_2.set_color(Color::red);
        window.attach(poly_2);


        Rectangle rect{Point{100,100}, 50, 100};
        rect.set_fill_color(Color::black);
        window.attach(rect);

        Image ii {Point{400, 200}, "some_imgs/morning_RPG_view.jpg"};
        window.attach(ii);

        window.wait_for_button();
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
