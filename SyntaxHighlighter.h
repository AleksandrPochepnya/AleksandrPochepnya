#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SyntaxHighlighter: public QSyntaxHighlighter{
    Q_OBJECT
    using BaseClass = QSyntaxHighlighter;
public:

    explicit SyntaxHighlighter(QTextDocument* parent = nullptr);
    void SetState(int state);

protected:

    virtual void highlightBlock(const QString &text) override;    

private:
    int State = 0;

};

#endif // SYNTAXHIGHLIGHTER_H
