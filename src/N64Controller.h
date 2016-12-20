#ifndef N64Controller_h
# define N64Controller_h

# include <Arduino.h>

class N64Controller {
    public:
        N64Controller(int pin);
        void init(void);
        /* void write(uint32_t); */
        /* void write2(uint32_t); */
        void writenoloop2(uint32_t);
        /* void write3(bool[]); */
        void writenoloop3(bool[]);
        void testLoop(void);
    private:
        int _pin;
        void write1(unsigned);
        void write0(unsigned);
        void writeStop(unsigned);
};
#endif
