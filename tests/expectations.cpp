#include <cstring>
#include "expectations.h"


const char* expected_text =
"class TestComponent extends Component{\n"
"    public int a = 0;\n"
"    public bool b;\n"
"    float c;\n"
"    //testing testing\n"
"    \n"
"    hook function(int p) {\n"
"        float d = 10;\n"
"        d += 5;\n"
"        string asd = \"hello\";\n"
"        if (d && des)\n"
"            return test;\n"
"        for (int i = 0; i < 20; i++) {\n"
"            \"\\\"\"\n"
"        }\n"
"        0x1230\n"
"        /*\n"
"            Multi line comment\n"
"        */\n"
"    }\n"
"}\n";


const unsigned int expected_text_length = strlen(expected_text);