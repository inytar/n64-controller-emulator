#ifndef N64Controller_h
# define N64Controller_h

# include <Arduino.h>

class N64Controller {
    public:
        N64Controller(int pin);
        void init(void);
        void write(uint32_t);
    private:
        int _pin;
        void write1(void);
        void write0(void);
        void writeStop(void);
};
#endif
