#ifndef GUI_H
#define GUI_H

#include <vector>
#include <string>

class HUD;
class GUI_Component;

class GUI
{
    public:
        GUI();
        ~GUI();

        std::vector<GUI_Component*> getComponentes(){return componentes;}

        void anyadirmenu   (int, int);
        void anyadirboton  (int, int, std::string);
        void anyadirtitulo (int, int, std::string);
        void anyadircontrol(int, int, std::string, std::string);
        void anyadirvolumen(int, int);

        void draw(int);
        void clean();
        void inicializar_hd();

    protected:

    private:

        std::vector<GUI_Component*> componentes;
        HUD* hud;

};

#endif // GUI_H