#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <vector>
#include <string>

#include <irrKlang.h>
#include "../lib/irrKlang/conio.h"

class SoundManager
{
    public:
        static SoundManager* getInstance() {
            static SoundManager singleton;
            return &singleton;
        }
        virtual ~SoundManager();

        typedef std::map<std::string, irrklang::ISoundSource*> SoundMap;
        typedef std::vector<irrklang::ISound*> SoundChannels;

        bool isCargado(std::string cadena);
        void cargarSonido(std::string cadena);
        void playSonido(std::string s);

        bool isPlaying(std::string s);

        void volumenGeneral(float f);
        void volumenSonido(float f, std::string s);

        void soundStop(irrklang::ISound* s){ s->stop(); }
        bool soundIsFinished(irrklang::ISound* s){ return s->isFinished(); }
        void Update();

    protected:

    private:
        SoundManager();
        irrklang::ISoundEngine* engine;

        SoundMap sonidos;
        SoundChannels canales;

};

#endif // SOUNDMANAGER_H