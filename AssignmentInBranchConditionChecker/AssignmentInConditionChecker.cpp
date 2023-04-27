/*
${workspaceFolder}/**
/home/caca/Documents/llvm-project/clang/include/**
/home/caca/Documents/llvm-project/llvm/include/**
/usr/include/llvm-10
/home/caca/Documents/llvm-project/build/tools/clang/include/** 
*/

#include "clang/AST/ASTVector.h"
#include "clang/AST/ComputeDependence.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclAccessPair.h"
#include "clang/AST/DependenceFlags.h"
#include "clang/AST/OperationKinds.h"
#include "clang/AST/TemplateBase.h"

#include "clang/Basic/CharInfo.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SyncScope.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/iterator.h"
#include "llvm/ADT/iterator_range.h"
#include "llvm/Support/AtomicOrdering.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/TrailingObjects.h"
#include <optional>

#include "clang/AST/APValue.h"
#include "clang/AST/ParentMap.h"
#include "clang/AST/Expr.h"
#include "clang/AST/Type.h"
#include "clang/AST/Stmt.h"
#include "clang/Basic/TypeTraits.h"
#include "clang/StaticAnalyzer/Checkers/BuiltinCheckerRegistration.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include <utility>
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>

using namespace clang;
using namespace ento;

namespace {

class AssignmentInConditionChecker: public Checker<check::BranchCondition> {

    mutable std::unique_ptr<BuiltinBug> BT;
    void ReportBug(const Expr *Ex, const std::string &Msg, CheckerContext &C) const;
    void checkAssignment(const Stmt *Statement, CheckerContext &Ctx) const;

    public:
        void checkBranchCondition(const Stmt *Condition, CheckerContext &Ctx) const;
    };
}

void AssignmentInConditionChecker::ReportBug(const Expr *Ex, const std::string &Msg, CheckerContext &C) const {

    if (ExplodedNode *N = C.generateNonFatalErrorNode()) {
        if (!BT){
            BT.reset(new BuiltinBug(this, "***BUGG***"));
        }

        C.emitReport(std::make_unique<PathSensitiveBugReport>(*BT, Msg.c_str(), N));
    }
}

void AssignmentInConditionChecker::checkAssignment(const Stmt *Statement, CheckerContext &Ctx) const {
    const Expr* expr=dyn_cast<Expr>(Statement);

    if(dyn_cast_or_null<ImplicitCastExpr>(expr)){
        ReportBug(expr,"Assignment is used as branch condition",Ctx);
        return;
    }

    if(const BinaryOperator *binOp = dyn_cast<BinaryOperator>(expr)) {
        if(binOp->isCommaOp()){
            expr = binOp->getLHS();
        
            while(const BinaryOperator *binOperator = dyn_cast_or_null<BinaryOperator>(expr)) {
          /*      if(!binOperator->isCommaOp()){
                    if(!(binOperator->isAssignmentOp() || binOperator->isCompoundAssignmentOp())){
                        ReportBug(expr,"Statement produces no effect",Ctx);
                        return;
                    }
                }
        */
                Expr* leftExpr = binOperator->getLHS();
                if(BinaryOperator *leftOp = dyn_cast<BinaryOperator>(leftExpr)) {
                    if(!leftOp->isCommaOp()){
                        if(!(leftOp->isAssignmentOp() || leftOp->isCompoundAssignmentOp())){
                            ReportBug(expr,"Statement produces no effect",Ctx);
                            return;
                        }
                    }
                }

                Expr* rightExpr = binOperator->getRHS();
                if(BinaryOperator *rightOp = dyn_cast<BinaryOperator>(rightExpr)) {
                    if(!(rightOp->isAssignmentOp() || rightOp->isCompoundAssignmentOp())){
                        ReportBug(rightExpr,"Statement produces no effect",Ctx);
                        return;    
                    }
                }
                expr = leftExpr;
            }
        }      
    }
}


void AssignmentInConditionChecker::checkBranchCondition(const Stmt *Condition, CheckerContext &Ctx) const {
    
    checkAssignment(Condition, Ctx);

}

void ento::registerAssignmentInConditionChecker(CheckerManager &mgr) {
    mgr.registerChecker<AssignmentInConditionChecker>();
}

bool ento::shouldRegisterAssignmentInConditionChecker(const CheckerManager &mgr) {
    return true;
}