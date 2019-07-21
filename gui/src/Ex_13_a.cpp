#include "std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

int main(){
    try {
        //
        using namespace Graph_lib; 
        cout << "Starting...\n";
        const int X_MAX = 1000;
    
        const int Y_MAX = 800;
        
        Point tl {100, 100};
        Simple_window window{tl, X_MAX, Y_MAX, "Exercises chap 13"};


        //ex 1
        Arc arc1 {Point{X_MAX/2, Y_MAX/2}, 100, 100, 0, 90};
        Point sig_start {0, Y_MAX}; //bottomleft corner
        Vector_ref<Arc> vec_arc;
        int color = 100;
        for(int i = 10; i < 400; i+=20){
            double decaying = 0.01*i;
            vec_arc.push_back(new Arc{sig_start, i, i, 0+decaying, 90-decaying});
            vec_arc[vec_arc.size()-1].set_color(Color(color++));
            window.attach(vec_arc[vec_arc.size()-1]);
        }

        //ex 2
        Box b1{Point{800, 600}, 100, 100, 20};
        b1.set_fill_color(Color::black);
        Box b2{Point{800, 600}, 150, 150, 20};
        Box b3{Point{800, 200}, 160, 160, 60};
        Box b4{Point{800, 400}, 160, 100, 30};
        b4.set_style(Line_style::dashdot);
        b4.set_fill_color(Color::cyan);
        b4.set_color(Color::dark_red);
        Ellipse e1{Point{600, 400}, 30, 40};
        e1.set_color(Color::dark_red);
        e1.set_fill_color(Color::dark_cyan);

        Immobile_Circle ic1{Point{400, 400}, 50};
        //ic1.move(400,0); //doesn't work

        window.attach(b1);
        window.attach(b2);
        window.attach(b3);
        window.attach(b4);
        window.attach(e1);
        window.attach(ic1);
        //window.attach(arc1);
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
