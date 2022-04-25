#include "sourcefile.h"

#include <QDebug>

SourceFile::SourceFile()
{

}

SourceFile::SourceFile(std::string n, std::string s, std::string c, std::string r) :
    name(n), status(s), creator(c), reviewer(r)
{
}

std::string SourceFile::toString() const
{
    return name + "," + status + "," + creator + "," + reviewer;
}
