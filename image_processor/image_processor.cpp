#include "pipeline.h"

int main(int argc, char** argv) {
    Pipeline pipeline;
    pipeline.CheckReference(argc);
    pipeline.Parse(argc, argv);
    pipeline.Run();
    return 0;
}
