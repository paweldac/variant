// Copyright (c) 2017 Pawel Dac
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/config.hpp"

#include "boost/test/minimal.hpp"
#include "boost/variant.hpp"
#include "boost/variant/apply_visitor.hpp"

#include <memory>
#include <functional>

template<typename T>
T foo(T value, std::unique_ptr<int>)
{
    return value;
}

using variant_type = boost::variant<int, double>;

void test_rvalue_mutable_inline_lambda_int_variant()
{
    int expectedIntValue = 10;
    variant_type v{expectedIntValue};
    std::unique_ptr<int> number(new int(42));

    auto valueFromVisitor = boost::apply_visitor(
        [capturedNumber = std::move(number)](const auto& msg) mutable -> auto {
            return foo(msg, std::move(capturedNumber));
        },
        v
    );

    BOOST_CHECK(valueFromVisitor == expectedIntValue);
}

void test_rvalue_mutable_inline_lambda_double_variant()
{
    double expectedDoubleValue = 15.0;
    variant_type v{expectedDoubleValue};
    std::unique_ptr<int> number(new int(42));

    auto valueFromVisitor = boost::apply_visitor(
        [capturedNumber = std::move(number)](const auto& msg) mutable -> auto {
            return foo(msg, std::move(capturedNumber));
        },
        v
    );

    BOOST_CHECK(valueFromVisitor == expectedDoubleValue);
}

void run_rvalue_mutable_visitor_tests()
{
    test_rvalue_mutable_inline_lambda_int_variant();
    test_rvalue_mutable_inline_lambda_double_variant();
}

int test_main(int , char* [])
{
    run_rvalue_mutable_visitor_tests();

    return 0;
}
