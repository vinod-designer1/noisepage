#pragma once

#include <execution/util/region_containers.h>

#include <memory>
#include <vector>

#include "execution/compiler/expression/expression_translator.h"
#include "execution/functions/function_context.h"

namespace terrier::parser {
class FunctionExpression;
}  // namespace terrier::parser

namespace terrier::execution::compiler {

/**
 * A translator for function expressions.
 */
class FunctionTranslator : public ExpressionTranslator {
 public:
  /**
   * Create a translator for the given derived value.
   * @param expr The expression to translate.
   * @param compilation_context The context in which translation occurs.
   */
  FunctionTranslator(const parser::FunctionExpression &expr, CompilationContext *compilation_context);

  /**
   * Derive the value of the expression.
   * @param ctx The context containing collected subexpressions.
   * @param provider A provider for specific column values.
   * @return The value of the expression.
   */
  ast::Expr *DeriveValue(WorkContext *ctx, const ColumnValueProvider *provider) const override;

  void DefineHelperFunctions(util::RegionVector<ast::FunctionDecl *> *decls) override;

 private:
  std::vector<const ExpressionTranslator> params_;
  ast::Identifier main_fn_;
//  common::ManagedPointer<functions::FunctionContext> udf_context_;
};
}  // namespace terrier::execution::compiler
