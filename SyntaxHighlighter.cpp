#include "SyntaxHighlighter.h"
#define binarryhex 2

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) : BaseClass(parent)
{
}

void SyntaxHighlighter::highlightBlock(const QString& text)
{
    bool flag = false;
    if(State == binarryhex){
        for (int i = 0; i < text.length(); ++i) {
            switch (i) {
            case 0:
                if(text.at(i).toLower() != "0"){
                    setFormat(i, 1, Qt::red);
                    flag = true;
                }
                break;

            case 1:
                if(text.at(i).toLower() != "x"){
                    setFormat(i, 1, Qt::red);
                    flag = true;
                }
                break;

            default:
                if ((text.at(i) != " " && text.at(i).toLower() != 'a' && text.at(i).toLower() != 'b' && text.at(i).toLower() != 'c'
                        && text.at(i).toLower() != 'd' && text.at(i).toLower() != 'f' && !text.at(i).isNumber()) || flag) {
                    flag = true;
                    setFormat(i, 1, Qt::red);
                }
                break;
            }
        }
    }
}

void SyntaxHighlighter::SetState(int state)
{
    State = state;
}

