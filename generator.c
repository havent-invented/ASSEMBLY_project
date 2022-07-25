#include <stdio.h>
#include "stdlib.h"

static _Bool MINUS_OP = 0;
static unsigned temp_counter = 0;


FILE *pFile;
FILE *inFile;
struct stack {
    double key;
    int sign;//number ,x , e, pi
    struct stack *next;
};

struct stack *createstack(char sign, double key) {
    struct stack *tmp = malloc(sizeof(struct stack));
    tmp->sign = sign;
    tmp->key = key;
    tmp->next = NULL;
    return tmp;
}

struct stack *pushs(char sign, double key, struct stack *old) {
    struct stack *tmp = malloc(sizeof(struct stack));
    tmp->sign = sign;//sign if
    tmp->key = key;
    tmp->next = old;
    return tmp;
}


FILE *reversePOLSKA(FILE *input)//Converts postfix to prefix polska
{//returns FILE * to stream with reversed function
    FILE *output = fopen("POLSKA.txt", "w");
    struct stack *st = createstack(0, 0);
    char key;
    fscanf(input, "%c", &key);
    while (key != '\n') {
        if (key == ' ')
            continue;
        if (key == '+' || key == '-' || key == '*' || key == '/') {
            int optype1 = st->sign;
            double op1 = st->key;
            struct stack *tmp = st->next;
            free(st);
            double op2 = tmp->key;
            int optype2 = tmp->sign;
            struct stack *tmp2 = tmp->next;
            free(tmp);
            st = tmp2;
            switch (optype2)//1-st op
            {
                case -1:
                    fprintf(output, "%c pi ", key);
                    break;
                case -2:
                    fprintf(output, "%c e ", key);
                    break;
                case -3:
                    fprintf(output, "%c x ", key);
                    break;
                case 0:
                    fprintf(output, "%c %lf ", key, op2);
                    break;
            }
            switch (optype1)//2-nd op
            {
                case -1:
                    fprintf(output, "pi ");
                    break;
                case -2:
                    fprintf(output, "e ");
                    break;
                case -3:
                    fprintf(output, "x ");
                    break;
                case 0:
                    fprintf(output, "%lf");
                    break;
            }
        } else {
            if (key >= '0' && key <= '9') {
                st = pushs(0, key, st);
            } else {
                if (key == 'p') {
                    st = pushs(-1, 0, st);
                    fscanf(input, "%c", &key);
                    continue;
                }
                if (key == 'e') {
                    st = pushs(-2, 0, st);
                    continue;
                }
                if (key == 'x') {
                    st = pushs(-3, 0, st);
                    continue;
                }
                int optype = st->sign;
                double op = st->key;
                struct stack *tmp = st->next;
                free(st);
                st = tmp;//1 op

                fscanf(input, "%c", &key);
                switch (key)//determinating function with 2-nd symbol
                {
                    case 'i':
                        fprintf(output, "sin ");
                        break;
                    case 'o':
                        fprintf(output, "cos ");
                        break;
                    case 'a':
                        fprintf(output, "tan ");
                        break;
                    case 't':
                        fprintf(output, "ctg ");
                        break;
                }
                switch (optype)//1 op
                {
                    case -1:
                        fprintf(output, "pi ");
                        break;
                    case -2:
                        fprintf(output, "e ");
                        break;
                    case -3:
                        fprintf(output, "x ");
                        break;
                    case 0:
                        fprintf(output, "%d ", op);
                        break;
                }
            };
        }
        fscanf(input, "%c", &key);
    }
    fclose(output);
    FILE *result = fopen("POLSKA.txt", "r");
}


struct tree {
    double key;
    int sign;
    /*
     0-- own constant
     -1 PI
     -2 E
     -3 x
     2 args:
     1 +
     2 -
     3 *
     4 /
     1 arg:
     5 sin
     6 cos
     7 tan
     8 ctg
     */
    struct tree *r;
    struct tree *l;
};


struct tree *create(int sign, double key) {
    struct tree *tmp = malloc(sizeof(struct tree));
    tmp->sign = sign;
    tmp->key = key;
    tmp->l = NULL;
    tmp->r = NULL;
    return tmp;
}

void delete_tree(struct tree *tree) {
    if (tree != NULL) {
        if (tree->r)
            delete_tree(tree->r);
        if (tree->l)
            delete_tree(tree->l);
        free(tree);
    }
    
}


struct tree *add() {
    char key;
    _Bool getnum = 0;
    do {
        fscanf(inFile, "%c", &key);
    } while (key == ' ');//skipping spaces

    struct tree *tmp;
    if ((!MINUS_OP && key == '-') || (key >= '0' && key <= '9')) {
        ungetc(key, inFile);
        getnum = 1;
        double inputval;
        int inputsign;
        //own constant case'
        inputsign = 0;
        fscanf(inFile, "%lf", &inputval);


        tmp = create(0, inputval);
    } else {
        //sign case
        int inputsign;
        switch (key) {//fist letter almost determinates sign//type
            case 'x':
                inputsign = -3;
                break;
            case 'e':
                inputsign = -2;
                break;
            case 'p':
                inputsign = -1;
                break;
            case '+':
                inputsign = 1;
                break;
            case '-':
                inputsign = 2;
                break;
            case '*':
                inputsign = 3;
                break;
            case '/':
                inputsign = 4;
                break;
            case 's':
                inputsign = 5;
                break;
            case 'c':
                fscanf(inFile, "%c", &key);
                if (key == 'o')//cos
                    inputsign = 6;
                else
                    inputsign = 8;//ctg case
                break;
            case 't'://tg
                inputsign = 7;
                break;
            default:
                inputsign = 0;
                break;
        }


        while (key != ' ') {// TODO/n check
            fscanf(inFile, "%c", &key);
            if (key == '\n')
                break;
        } //till space,preparing for new input
        ungetc(key, inFile);


        struct tree *tmp1 = NULL;
        struct tree *tmp2 = NULL;

        if (inputsign < 5 && inputsign > 0)//2-operand sign
        {
            tmp1 = add();
            tmp2 = add();
        }
        if (inputsign >= 5) {
            tmp1 = add();
        }
        tmp = create(inputsign, 0);
        tmp->l = tmp1;
        tmp->r = tmp2;

    }
    return tmp;
}


struct tree *deriv(struct tree *tree) {
    struct tree *der = create(0, 0);
    if (tree->sign == -3) {
        der->key = 1;
        return der;
    }//x case
    if (tree->sign <= 0)//constant not x
    {
        der->key = 0;
        return der;
    }
    if (tree->sign == 1)//+
    {
        der->sign = 1;
        der->r = deriv(tree->r);
        der->l = deriv(tree->l);
        return der;
    }
    if (tree->sign == 2)//-
    {
        der->sign = 2;
        der->r = deriv(tree->r);
        der->l = deriv(tree->l);
        return der;
    }

    if (tree->sign == 3) {
        der->sign = 1;

        struct tree *derL = deriv(tree->l);
        struct tree *derR = deriv(tree->r);

        der->r = create(3, 0);
        der->l = create(3, 0);

        der->l->l = derL;
        der->l->r = tree->r;

        der->r->l = tree->l;
        der->r->r = derR;
        return der;
    }

    if (tree->sign == 4)// /
    {
        der->sign = 4;

        struct tree *derL = deriv(tree->l);
        struct tree *derR = deriv(tree->r);
        //numerator
        der->l = create(2, 0);

        der->l->l = create(3, 0);
        der->l->r = create(3, 0);

        der->l->l->l = derL;
        der->l->l->r = tree->r;

        der->l->r->l = tree->l;
        der->l->r->r = derR;



        //denumirator
        der->r = create(3, 0);
        der->r->r = tree->r;
        der->r->l = tree->r;


        return der;
    }
    if (tree->sign == 5)//sin
    {
        der->sign = 3;
        der->l = create(6, 0);
        der->l->l = tree->l;

        der->r = deriv(tree->l);
        return der;
    }

    if (tree->sign == 6)//cos
    {

        der->sign = 3;
        der->l = create(5, 0);
        der->l->l = tree->l;

        der->r = create(3, 0);
        der->r->l = create(0, -1);
        der->r->r = deriv(tree->l);


        return der;
    }
    if (tree->sign == 7) {
        der->sign = 4;
        der->l = deriv(tree->l);

        der->r = create(3, 0);
        der->r->l = create(6, 0);
        der->r->l->l = tree->l;
        der->r->r = tree->r->l;

        return der;
    }

    if (tree->sign == 8) {
        der->sign = 4;
        der->l = create(3, 0);
        der->l->r = create(0, -1);
        der->l->l = deriv(tree->l);


        der->r = create(3, 0);
        der->r->l = create(5, 0);
        der->r->l->l = tree->l;
        der->r->r = tree->r->l;

        return der;
    }


}


void memory_intit(struct tree *tree) {
    if (tree) {
        if (tree->sign == 0)
            fprintf(pFile, "const%u dq %lf\n", temp_counter, tree->key);
        else {
            fprintf(pFile, "const%u dq 0\n", temp_counter);
        }
        temp_counter++;
        if (tree->l) {
            memory_intit(tree->l);
        }
        if (tree->r) {
            memory_intit(tree->r);
        }
    }
}

void Printer(struct tree *tree)//for each separatly  F
{
    if (tree->sign == 0) {
        //fprintf(pFile,"fld qword[const%u]\n", temp_counter);

    }
    if (tree->sign == -3) {//x
        fprintf(pFile, "fld qword [ebp + 8]\n");
        fprintf(pFile, "fstp qword [const%u]\n", temp_counter);
    }
    if (tree->sign == -2)//e
    {
        fprintf(pFile, "fld qword [E_const]\n");
        fprintf(pFile, "fstp qword [const%u]\n", temp_counter);
    }
    if (tree->sign == -1) {//pi
        fprintf(pFile, "FLDPI\n");
        fprintf(pFile, "fstp qword [const%u]\n", temp_counter);
    }
    if (tree->sign >= 5) {//1 op
        unsigned saved = temp_counter;
        temp_counter++;
        Printer(tree->l);

        fprintf(pFile, "fld qword[const%u]\n", saved + 1);
        switch (tree->sign) {
            case 5:
                fprintf(pFile, "FSIN\n");
                break;
            case 6:
                fprintf(pFile, "FCOS\n");
                break;
            case 7:
                fprintf(pFile, "FPTAN\n");
                fprintf(pFile, "FSTP qword[tmp]\n");
                break;
            case 8:
                fprintf(pFile, "FPTAN\n");//st0=1 st1=tan
                fprintf(pFile, "FDIVRP\n");//ctg
                break;
        }

        fprintf(pFile, "FSTP qword[const%u]\n", saved);
        temp_counter++;
    }

    if (tree->sign < 5 && tree->sign > 0) {//2 op
        unsigned saved = temp_counter;//element
        temp_counter++;
        Printer(tree->l);
        temp_counter++;
        unsigned saved2 = temp_counter;//right son

        Printer(tree->r);
        fprintf(pFile, "fld qword[const%u]\n", saved2);//left son
        fprintf(pFile, "fld qword[const%u]\n", saved + 1);
        switch (tree->sign) {
            case 1:
                fprintf(pFile, "FADDP\n");
                break;
            case 2:
                fprintf(pFile, "FSUBRP\n");
                break;
            case 3:
                fprintf(pFile, "FMULP\n");
                break;
            case 4:
                fprintf(pFile, "FDIVRP\n");
                break;
        }
        fprintf(pFile, "FSTP qword[const%u]\n", saved);
        //temp_counter++;
    }
}


void generator() {//generate code for all F
    //first--
    pFile = fopen("func.s", "w");



    //init
    fprintf(pFile, "section .data\n");
    fprintf(pFile, "E_const dq 2.7182818\n");
    fprintf(pFile, "tmp dq 0\n");
    fprintf(pFile, "x dq 0\n");
    fprintf(pFile, "global F1\n");
    fprintf(pFile, "global F2\n");
    fprintf(pFile, "global F3\n");
    fprintf(pFile, "global Der1\n");
    fprintf(pFile, "global Der2\n");
    fprintf(pFile, "global Der3\n");

    _Bool reversePolskaneed = 0;//convert prefix to postfix
    
    struct tree *tree1;
    struct tree *tree2;
    struct tree *tree3;
    
    
    if (reversePolskaneed) {
        char key;
        //funcltion trees
        FILE *tmp;

        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);

        FILE *inFile1 = reversePOLSKA(inFile);
        tmp = inFile1;
        inFile1 = inFile;
        inFile = tmp;
        tree1 = add();
        tmp = inFile1;
        inFile1 = inFile;
        inFile = tmp;

        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);
        inFile1 = reversePOLSKA(inFile);

        tmp = inFile1;
        inFile1 = inFile;
        inFile = tmp;
        tree2 = add();
        tmp = inFile1;
        inFile1 = inFile;
        inFile = tmp;

        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);
        inFile1 = reversePOLSKA(inFile);

        tmp = inFile1;
        inFile1 = inFile;
        inFile = tmp;
        tree3 = add();
        tmp = inFile1;
        inFile1 = inFile;
        inFile = tmp;

        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);
    } else {

        char key;
        //funcltion trees
        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);
        tree1 = add();

        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);
        tree2 = add();

        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);

        tree3 = add();
        fscanf(inFile, "%c", &key);
        if (key != '\n')
            ungetc(key, inFile);

    }
    //memory inizialisation

    memory_intit(tree1);
    fprintf(pFile, "\n");
    unsigned len1 = temp_counter;
    memory_intit(tree2);
    fprintf(pFile, "\n");
    unsigned len2 = temp_counter - len1;
    fprintf(pFile, "\n");
    memory_intit(tree3);
    unsigned len3 = temp_counter - len2 - len1;
fprintf(pFile, "\n");
	fprintf(pFile, "\n;\n");
    //derivetives    

    struct tree *der1 = deriv(tree1);
    struct tree *der2 = deriv(tree2);
    struct tree *der3 = deriv(tree3);

    //memory init for deriv trees
    memory_intit(der1);
    fprintf(pFile, "\n");
    unsigned derlen1 = temp_counter - len2 - len1 - len3;
    memory_intit(der2);
    fprintf(pFile, "\n");
    unsigned derlen2 = temp_counter - len2 - len1 - len3 - derlen1;
    memory_intit(der3);
    fprintf(pFile, "\n");
    unsigned derlen3 = temp_counter - len2 - len1 - len3 - derlen1 - derlen2;
	
	


    //struct tree *tree2 = add();
    //struct tree *tree3 = add();
    temp_counter = 0;


    fprintf(pFile, "F1:\npush ebp\nmov ebp, esp \n");
    fprintf(pFile, "finit\n");
    Printer(tree1);
    fprintf(pFile, "fld qword[const0]\n");
    fprintf(pFile, "pop ebp\nret\n");


    temp_counter = len1;
    fprintf(pFile, "F2:\npush ebp\nmov ebp, esp \n");
    fprintf(pFile, "finit\n");
    Printer(tree2);
    fprintf(pFile, "fld qword[const%u]\n", len1);
    fprintf(pFile, "pop ebp\nret\n");


    temp_counter = len1 + len2;
    fprintf(pFile, "F3:\npush ebp\nmov ebp, esp \n");
    fprintf(pFile, "finit\n");
    Printer(tree3);
    fprintf(pFile, "fld qword[const%u]\n", len1 + len2);
    fprintf(pFile, "pop ebp\nret\n");

    //derivetives
    temp_counter = len1 + len2 + len3;
    fprintf(pFile, "Der1:\npush ebp\nmov ebp, esp \n");
    fprintf(pFile, "finit\n");
    Printer(der1);
    fprintf(pFile, "fld qword[const%u]\n", len1 + len2 + len3);
    fprintf(pFile, "pop ebp\nret\n");

    temp_counter = len1 + len2 + len3 + derlen1;
    fprintf(pFile, "Der2:\npush ebp\nmov ebp, esp \n");
    fprintf(pFile, "finit\n");
    Printer(der2);
    fprintf(pFile, "fld qword[const%u]\n", len1 + len2 + len3 + derlen1);
    fprintf(pFile, "pop ebp\nret\n");

    temp_counter = len1 + len2 + len3 + derlen1 + derlen2;
    fprintf(pFile, "Der3:\npush ebp\nmov ebp, esp \n");
    fprintf(pFile, "finit\n");
    Printer(der3);
    fprintf(pFile, "\n");
    fprintf(pFile, "fld qword[const%u]\n", len1 + len2 + len3 + derlen1 + derlen2);
    fprintf(pFile, "pop ebp\nret\n");

    delete_tree(tree1);
    delete_tree(tree2);
    delete_tree(tree3);

    fclose(pFile);
}

int main(int argc, char **argv) {
    //setbuf(stdout,0);
    char defstr[7] = "in.txt";
    char *str = defstr;
    FILE *tmpFile = fopen("filename", "w");//passing input file name to main function
    if (argc > 1)
        str = argv[1];
    inFile = fopen(str, "r");
    fputs(str, tmpFile);
    fclose(tmpFile);
    char tmpc = '\n';// skipping \n and ' '

    double interval;
    fscanf(inFile, "%lf", &interval);
    fscanf(inFile, "%lf", &interval);

    while (tmpc == '\n' || tmpc == ' ') {
        fscanf(inFile, "%c", &tmpc);
    }
    ungetc(tmpc, inFile);

    generator();

    fclose(inFile);
    return 0;
}
