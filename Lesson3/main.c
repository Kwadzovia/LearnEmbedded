int counter = 0;

int main() {
    int *p_int;
    p_int = &counter;
    
    while(*p_int < 21){
        ++(*p_int);
    }
    
    p_int = (int *)0x20000002U;
    *p_int = 0xDEADBEEF; //Note that this is misalligned at address 0x20000000
    
    
    return 0;
}
