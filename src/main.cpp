#include "application/application.h"

int main() {

    Application app(1600, 900, "gentracer");

    app.init();

    app.run();

    app.destroy(); 

    return 0;

}
