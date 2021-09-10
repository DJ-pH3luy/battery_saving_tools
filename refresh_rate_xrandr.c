#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void set_rate(int ac_status){
    if (ac_status == 1){
        system("/usr/bin/xrandr -r 144");
    } else {
        system("/usr/bin/xrandr -r 60");
    }
}

void gnome_animations(int ac_status){
    if (ac_status == 1){
        system("gsettings set org.gnome.desktop.interface enable-animations true");
    } else {
        system("gsettings set org.gnome.desktop.interface enable-animations false");
    }
}

int check_ac(){
    char c[10];
    FILE *fptr;
    int status;
    if ((fptr = fopen("/sys/class/power_supply/AC0/online", "r")) == NULL) {
        printf("/sys/class/power_supply/AC0/online not found");
        exit(1);
    }
    fscanf(fptr, "%[^\n]", c);
    status = atoi(c);
    fclose(fptr);
    return status;
}

int main(){
    int old_status = check_ac();
    set_rate(old_status);
    gnome_animations(old_status);
    int new_status;
    while (1)
    {
        sleep(2);
        new_status = check_ac();
        if (new_status != old_status) {
            // just comment out the things you don't want/need
            set_rate(new_status);
            gnome_animations(new_status);
            old_status = new_status;
        }
    }
    
}