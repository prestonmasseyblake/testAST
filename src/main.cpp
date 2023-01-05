#include <set>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace std;
struct MyStruct
{
    std::string name;
    DeclarationMatcher declMatcher;
    MyStruct(const std::string &Name) : name(Name), declMatcher(functionDecl(hasName(Name)).bind("functionDecl")) {}
};

class MyStructHandler : public MatchFinder::MatchCallback
{
public:
    MyStructHandler(const MyStruct &Struct) : myStruct(Struct) {}
    virtual void run(const MatchFinder::MatchResult &Result)
    {
        if (const FunctionDecl *functionDecl = Result.Nodes.getNodeAs<FunctionDecl>("functionDecl"))
        {
            std::cout<<"it's working"<<std::endl;
        }
    }
private:
    const MyStruct &myStruct;
};

int main(int argc, const char **argv)
{
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    std::set<MyStruct> structSet;

    MyStruct struct1("Dr Kredo");
    MyStruct struct2("Jorge");
    MyStruct struct3("NAvi");

    structSet.insert(struct1);
    structSet.insert(struct2);

    MatchFinder finder;
    for (const MyStruct &myStruct : structSet)
    {
        MyStructHandler handler(myStruct);
        finder.addMatcher(myStruct.declMatcher, &handler);
    }

    return Tool.run(newFrontendActionFactory(&finder).get());
}