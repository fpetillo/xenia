/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "alloy/test/util.h"

using namespace alloy;
using namespace alloy::hir;
using namespace alloy::runtime;
using namespace alloy::test;
using alloy::frontend::ppc::PPCContext;

TEST_CASE("SWIZZLE_V128", "[instr]") {
  TestFunction([](hir::HIRBuilder& b) {
                 StoreVR(b, 3, b.Swizzle(LoadVR(b, 4), INT32_TYPE,
                                         SWIZZLE_MASK(0, 1, 2, 3)));
                 b.Return();
               }).Run([](PPCContext* ctx) { ctx->v[4] = vec128i(0, 1, 2, 3); },
                      [](PPCContext* ctx) {
                        auto result = ctx->v[3];
                        REQUIRE(result == vec128i(0, 1, 2, 3));
                      });
  TestFunction([](hir::HIRBuilder& b) {
                 StoreVR(b, 3, b.Swizzle(LoadVR(b, 4), INT32_TYPE,
                                         SWIZZLE_MASK(3, 2, 1, 0)));
                 b.Return();
               }).Run([](PPCContext* ctx) { ctx->v[4] = vec128i(0, 1, 2, 3); },
                      [](PPCContext* ctx) {
                        auto result = ctx->v[3];
                        REQUIRE(result == vec128i(3, 2, 1, 0));
                      });
  TestFunction([](hir::HIRBuilder& b) {
                 StoreVR(b, 3, b.Swizzle(LoadVR(b, 4), INT32_TYPE,
                                         SWIZZLE_MASK(1, 1, 2, 2)));
                 b.Return();
               }).Run([](PPCContext* ctx) { ctx->v[4] = vec128i(0, 1, 2, 3); },
                      [](PPCContext* ctx) {
                        auto result = ctx->v[3];
                        REQUIRE(result == vec128i(1, 1, 2, 2));
                      });
}
