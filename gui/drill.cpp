#include "std_lib_facilities.h"
#include "support_code/Simple_window.h"
#include "support_code/Window.h"
#include "support_code/Graph.h"


int main(){
    try {
        //
        
        using namespace Graph_lib;
        Simple_window win {Point(100, 100), 800, 600, "Drill"};
        Rectangle rr {Point{0, 0}, 100, 30};
        Text tr {Point{30, 15}, "Howdy!"};
        //win.attach(rr);
        //win.attach(tr);

        Text ti {Point{100, 150}, "V.O."};
        ti.set_font_size(150);
        ti.set_style(Line_style::solid);
        //win.attach(ti);

        Polygon p1;
        p1.add(Point{300, 200});
        p1.add(Point{400, 300});
        p1.add(Point{700, 500});
        //win.attach(p1);
        
        Point se_center {400, 300};

        double a = 100;
        double b = 50;
        double m = 2.0;
        double n = 4.0;
        Open_polyline se1;
        se1.set_color(Color::blue);
        Open_polyline se2;
        se2.set_color(Color::red);
        Open_polyline se3;
        se3.set_color(Color::cyan);
        Open_polyline se4;
        se4.set_color(Color::green);

        for(int y = -b; y <= 0; ++y) {
            int x1 = a*pow(1-pow(abs(y/b),n), 1/m);
            int x2 = -x1;
            se1.add(Point{x1+se_center.x, y+se_center.y});
            se2.add(Point{x2+se_center.x, y+se_center.y});
        }
        for(int y = b; y>=0; --y) {
            int x3 = a*pow(1-pow(abs(y/b),n), 1/m);
            int x4 = -x3;
            se3.add(Point{x3+se_center.x, y+se_center.y});
            se4.add(Point{x4+se_center.x, y+se_center.y});
        }


        win.attach(se1);
        win.attach(se2);
        win.attach(se3);
        win.attach(se4);

        //Point center(win.x_max() / 2, win.y_max() / 2);
        //Graph_lib::Open_polyline supEllipse0;
        //supEllipse0.set_color(Color::red);
        //Graph_lib::Open_polyline supEllipse1;
        //supEllipse1.set_color(Color::green);
        //Graph_lib::Open_polyline supEllipse2;
        //supEllipse2.set_color(Color::blue);
        //Graph_lib::Open_polyline supEllipse3;
        //supEllipse3.set_color(Color::black);
     
        //double a = 100;
        //double y;
        //double b = 100;
        //double n; // 1/2; 3/2; 2; 4;
        //n = 2.0;
     
        //for (int x = -100; x < 0; x++) {
        //    y = b * pow(1 - pow(abs(x / a), n), 1 / n);
        //    supEllipse0.add(Point(x + center.x, y + center.y));
        //}
        //for (int x = 0; x < 101; x++) {
        //    y = b * pow(1 - pow(abs(x / a), n), 1 / n);
        //    supEllipse1.add(Point(x + center.x, y + center.y));
        //}
     
        //for (int x = 100; x > 0; x--) {
        //    y = b * pow(1 - pow(abs(x / a), n), 1 / n);
        //    y = -y;
        //    supEllipse2.add(Point(x + center.x, y + center.y));
        //}
     
        //for (int x = 0; x > -101; x--) {
        //    y = b * pow(1 - pow(abs(x / a), n), 1 / n);
        //    y = -y;
        //    supEllipse3.add(Point(x + center.x, y + center.y));
        //}
     
        //win.attach(supEllipse0);
        //win.attach(supEllipse1);
        //win.attach(supEllipse2);
        //win.attach(supEllipse3);       //win.attach(se4);
        
        win.wait_for_button();
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
