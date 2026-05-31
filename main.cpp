#include <unistd.h>
#include <iostream>
#include <ft/ft.hpp>
#include <math.h>


int main() {
    ft::TXT txt("auto");

  
    ft::Encoder m1(txt, 1);
    ft::Encoder m2(txt, 2);

    ft::Motor m3(txt, 3);

    ft::Switch s1(txt, 1);
    ft::Switch s2(txt, 2);
    ft::Switch s8(txt, 8);

    txt.update_config();
    usleep(1000000);

    m1.startSpeed(-300);
    m2.startSpeed(-300);
    bool m1_running = true;
    bool m2_running = true;

    
    while (m1_running || m2_running){
        if (s8.getState() == 1){  
            m1.startDistance(0);
            m1.stop(1);
            m2.startDistance(0);
            m2.stop(2);
            m1_running = m2_running = false;
        }
        if (m1_running && s1.getState() == 1){
            m1.startDistance(0);
            m1.stop(1);
            m1_running = false;
        }
        if (m2_running && s2.getState() == 1){
            m2.startDistance(0);
            m2.stop(2);
            m2_running = false;
        }
    }


    int x_pos = 0;
    int y_pos = 0;

    bool pen_down = false;
    m3.startSpeed(512);
    usleep(1000000);
    m3.stop();
    bool quit = false;

    while (!quit){
        int input1 = 0;
        int input2 = 0;
        std::cin >> input1;

        if (std::cin.fail()){
            quit = true;
        }
        else{        
        
            std::cin >> input2;

            if (input1 > 0){m1.startSpeed(300);}
            
            else{m1.startSpeed(-300);}
            //if (input1 != 0){m1.startDistance(std::abs(input1));}

            if (input2 > 0){m2.startSpeed(300);}

            else{m2.startSpeed(-300);}
            //if (input2 != 0){m2.startDistance(std::abs(input2));}
            m1_running = true;
            m2_running = true;
            while (m1_running || m2_running) {
                if (s8.getState() == 1){  
                    m1.resetDistance();
                    m1.stop(1);
                    m2.startDistance(0);
                    m2.stop(2);
                    m1_running = m2_running = false;
                }
                if (m1.getCurrentDistance() >= std::abs(input1)){
                    m1.startDistance(0);
                    m1.stop(1);
                    m1_running = false;
                }
                if (m2.getCurrentDistance() >= std::abs(input2)){
                    m2.startDistance(0);
                    m2.stop(2);
                    m2_running = false;
                }
                std::cout << m1.getCurrentDistance() << "\n"  << m2.getCurrentDistance()  << "\n";
                //std::cout << m1_running << m2_running;


            }
        }

    }


    std::cout << "Fertig!" << std::endl;

    m3.startSpeed(-512);
    usleep(1000000);
    m3.stop();
    return 0;
}

//1970 buffer 12 
//1190 buffer 18



//ft@192.168.7.2
//fischertechnik