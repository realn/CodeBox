//
// Created by noname on 2.01.2026.
//

#include <vector>
#include <set>
#include <unordered_set>

#include <gtest/gtest.h>

import realn.codebox.core;

TEST(cbcore_strings, conversion) {
    using namespace std::string_literals;

    //simple cast
    EXPECT_EQ(realn::cb::cast_string_to_u8("some text"), std::u8string{u8"some text"});

    //simple conversion
    EXPECT_EQ(realn::cb::utf_convert_to_u8(u"some text"), std::u8string{u8"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u8(U"some text"), std::u8string{u8"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(u8"some text"), std::u16string{u"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(U"some text"), std::u16string{u"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u8"some text"), std::u32string{U"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u"some text"), std::u32string{U"some text"});

    //more complex conversions
    EXPECT_EQ(realn::cb::utf_convert_to_u8(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u8string{u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u8(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u8string{u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u16string{u"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u16string{u"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u32string{U"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u32string{U"źdźbło trawy ścieka w szczękę dżdżownicy równo"});

    //complex conversions
    EXPECT_EQ(realn::cb::utf_convert_to_u8(u"複雑なものと単純なものは同じである"),
              std::u8string{u8"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u8(U"複雑なものと単純なものは同じである"),
              std::u8string{u8"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(u8"複雑なものと単純なものは同じである"),
              std::u16string{u"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(U"複雑なものと単純なものは同じである"),
              std::u16string{u"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u8"複雑なものと単純なものは同じである"),
              std::u32string{U"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u"複雑なものと単純なものは同じである"),
              std::u32string{U"複雑なものと単純なものは同じである"});
}

TEST(cbcore_strings, bool_conversion) {
    using namespace std::string_literals;
    using namespace realn;

    EXPECT_EQ(cb::bool_to_string(true), "true"s);
    EXPECT_EQ(cb::bool_to_string(false), "false"s);
    EXPECT_EQ(cb::bool_to_string(true, cb::to_string_conv_type::LOWER), "true"s);
    EXPECT_EQ(cb::bool_to_string(false, cb::to_string_conv_type::LOWER), "false"s);
    EXPECT_EQ(cb::bool_to_string(true, cb::to_string_conv_type::CAPITALIZED), "True"s);
    EXPECT_EQ(cb::bool_to_string(false, cb::to_string_conv_type::CAPITALIZED), "False"s);
    EXPECT_EQ(cb::bool_to_string(true, cb::to_string_conv_type::HIGHER), "TRUE"s);
    EXPECT_EQ(cb::bool_to_string(false, cb::to_string_conv_type::HIGHER), "FALSE"s);

    EXPECT_EQ(cb::bool_to_utf8(true), u8"true"s);
    EXPECT_EQ(cb::bool_to_utf8(false), u8"false"s);
    EXPECT_EQ(cb::bool_to_utf8(true, cb::to_string_conv_type::LOWER), u8"true"s);
    EXPECT_EQ(cb::bool_to_utf8(false, cb::to_string_conv_type::LOWER), u8"false"s);
    EXPECT_EQ(cb::bool_to_utf8(true, cb::to_string_conv_type::CAPITALIZED), u8"True"s);
    EXPECT_EQ(cb::bool_to_utf8(false, cb::to_string_conv_type::CAPITALIZED), u8"False"s);
    EXPECT_EQ(cb::bool_to_utf8(true, cb::to_string_conv_type::HIGHER), u8"TRUE"s);
    EXPECT_EQ(cb::bool_to_utf8(false, cb::to_string_conv_type::HIGHER), u8"FALSE"s);

    EXPECT_EQ(cb::bool_to_utf16(true), u"true"s);
    EXPECT_EQ(cb::bool_to_utf16(false), u"false"s);
    EXPECT_EQ(cb::bool_to_utf16(true, cb::to_string_conv_type::LOWER), u"true"s);
    EXPECT_EQ(cb::bool_to_utf16(false, cb::to_string_conv_type::LOWER), u"false"s);
    EXPECT_EQ(cb::bool_to_utf16(true, cb::to_string_conv_type::CAPITALIZED), u"True"s);
    EXPECT_EQ(cb::bool_to_utf16(false, cb::to_string_conv_type::CAPITALIZED), u"False"s);
    EXPECT_EQ(cb::bool_to_utf16(true, cb::to_string_conv_type::HIGHER), u"TRUE"s);
    EXPECT_EQ(cb::bool_to_utf16(false, cb::to_string_conv_type::HIGHER), u"FALSE"s);

    EXPECT_EQ(cb::bool_to_utf32(true), U"true"s);
    EXPECT_EQ(cb::bool_to_utf32(false), U"false"s);
    EXPECT_EQ(cb::bool_to_utf32(true, cb::to_string_conv_type::LOWER), U"true"s);
    EXPECT_EQ(cb::bool_to_utf32(false, cb::to_string_conv_type::LOWER), U"false"s);
    EXPECT_EQ(cb::bool_to_utf32(true, cb::to_string_conv_type::CAPITALIZED), U"True"s);
    EXPECT_EQ(cb::bool_to_utf32(false, cb::to_string_conv_type::CAPITALIZED), U"False"s);
    EXPECT_EQ(cb::bool_to_utf32(true, cb::to_string_conv_type::HIGHER), U"TRUE"s);
    EXPECT_EQ(cb::bool_to_utf32(false, cb::to_string_conv_type::HIGHER), U"FALSE"s);

    bool result = false;
    EXPECT_THROW(cb::string_to_bool("invalid"s), std::runtime_error);
    EXPECT_NO_THROW(cb::string_to_bool("invalid"s, &result));

    EXPECT_EQ(cb::string_to_bool("true"s), true);
    EXPECT_EQ(cb::string_to_bool("True"s), true);
    EXPECT_EQ(cb::string_to_bool("TRUE"s), true);
    EXPECT_EQ(cb::string_to_bool(u8"true"s), true);
    EXPECT_EQ(cb::string_to_bool(u8"True"s), true);
    EXPECT_EQ(cb::string_to_bool(u8"TRUE"s), true);
    EXPECT_EQ(cb::string_to_bool(u"true"s), true);
    EXPECT_EQ(cb::string_to_bool(u"True"s), true);
    EXPECT_EQ(cb::string_to_bool(u"TRUE"s), true);
    EXPECT_EQ(cb::string_to_bool(U"true"s), true);
    EXPECT_EQ(cb::string_to_bool(U"True"s), true);
    EXPECT_EQ(cb::string_to_bool(U"TRUE"s), true);

    EXPECT_EQ(cb::string_to_bool("false"s), false);
    EXPECT_EQ(cb::string_to_bool("False"s), false);
    EXPECT_EQ(cb::string_to_bool("FALSE"s), false);
    EXPECT_EQ(cb::string_to_bool(u8"false"s), false);
    EXPECT_EQ(cb::string_to_bool(u8"False"s), false);
    EXPECT_EQ(cb::string_to_bool(u8"FALSE"s), false);
    EXPECT_EQ(cb::string_to_bool(u"false"s), false);
    EXPECT_EQ(cb::string_to_bool(u"False"s), false);
    EXPECT_EQ(cb::string_to_bool(u"FALSE"s), false);
    EXPECT_EQ(cb::string_to_bool(U"false"s), false);
    EXPECT_EQ(cb::string_to_bool(U"False"s), false);
    EXPECT_EQ(cb::string_to_bool(U"FALSE"s), false);
}

TEST(cbcore_strings, utf_length) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_str = "some_text"s;
    const auto test_text_utf8 = u8"some text"s;

    EXPECT_EQ(cb::utf_length(test_text_str), 9);
    EXPECT_EQ(cb::utf_length(test_text_str), test_text_str.length());
    EXPECT_EQ(cb::utf_length(test_text_utf8), 9);
    EXPECT_EQ(cb::utf_length(test_text_utf8), test_text_utf8.length());

    const auto test_text2_str = "サンプル"s;
    const auto test_text2_utf8 = u8"サンプル"s;

    EXPECT_EQ(cb::utf_length(test_text2_str), 4);
    EXPECT_NE(cb::utf_length(test_text2_str), test_text2_str.length());
    EXPECT_EQ(cb::utf_length(test_text2_utf8), 4);
    EXPECT_NE(cb::utf_length(test_text2_utf8), test_text2_utf8.length());
}

TEST(cbcore_strings, utf_bom) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_str = "some_text"s;
    const auto test_text_utf8 = u8"some text"s;

    const auto test_text_with_bom_str = "\xef\xbb\xbfsome_text"s;
    const auto test_text_with_bom_utf8 = u8"\xef\xbb\xbfsome text"s;

    const auto wrong_bom_str = test_text_str + test_text_with_bom_str;
    const auto wrong_bom_utf8 = test_text_utf8 + test_text_with_bom_utf8;

    EXPECT_FALSE(cb::starts_with_utf8_bom(test_text_str));
    EXPECT_FALSE(cb::starts_with_utf8_bom(test_text_utf8));

    EXPECT_TRUE(cb::starts_with_utf8_bom(test_text_with_bom_str));
    EXPECT_TRUE(cb::starts_with_utf8_bom(test_text_with_bom_utf8));

    EXPECT_FALSE(cb::starts_with_utf8_bom(wrong_bom_str));
    EXPECT_FALSE(cb::starts_with_utf8_bom(wrong_bom_utf8));
}

TEST(cbcore_strings, utf8_validation) {
    using namespace std::string_literals;
    using namespace realn;

    const auto valid_text1_str = "some_text"s;
    const auto valid_text2_str = "źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto valid_text3_str = "複雑なものと単純なものは同じである"s;

    const auto valid_text1_utf8 = u8"some_text"s;
    const auto valid_text2_utf8 = u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto valid_text3_utf8 = u8"複雑なものと単純なものは同じである"s;

    const auto invalid_text1_str = "\x43\xf1\xf4"s;
    const auto invalid_text2_str = "źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_str = "複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    const auto invalid_text1_utf8 = u8"\x43\xf1\xf4"s;
    const auto invalid_text2_utf8 = u8"źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_utf8 = u8"複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_str));

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_utf8));

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_str));

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_utf8));
}

TEST(cbcore_strings, invalid_utf8_replace) {
    using namespace std::string_literals;
    using namespace realn;

    const auto invalid_text1_str = "\x43\xf1\xf4"s;
    const auto invalid_text2_str = "źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_str = "複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    const auto invalid_text1_utf8 = u8"\x43\xf1\xf4"s;
    const auto invalid_text2_utf8 = u8"źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_utf8 = u8"複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_str));

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_utf8));

    const auto valid_text1_str = cb::replace_invalid_utf8(invalid_text1_str, '!');
    const auto valid_text2_str = cb::replace_invalid_utf8(invalid_text2_str, '!');
    const auto valid_text3_str = cb::replace_invalid_utf8(invalid_text3_str, '!');

    const auto valid_text1_utf8 = cb::replace_invalid_utf8(invalid_text1_utf8, '!');
    const auto valid_text2_utf8 = cb::replace_invalid_utf8(invalid_text2_utf8, '!');
    const auto valid_text3_utf8 = cb::replace_invalid_utf8(invalid_text3_utf8, '!');

    EXPECT_EQ(valid_text1_str, "C!!"s);
    EXPECT_EQ(valid_text2_str, "źdź!ło trawy ścieka w!szczękę dżdżownicy równo"s);
    EXPECT_EQ(valid_text3_str, "複雑なもの\x01と単純なも!のは同じで!ある"s);

    EXPECT_EQ(valid_text1_utf8, u8"C!!"s);
    EXPECT_EQ(valid_text2_utf8, u8"źdź!ło trawy ścieka w!szczękę dżdżownicy równo"s);
    EXPECT_EQ(valid_text3_utf8, u8"複雑なもの\x01と単純なも!のは同じで!ある"s);

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_str));

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_utf8));
}

TEST(cbcore_strings, count) {
    using namespace std::string_literals;
    using namespace realn;

    EXPECT_EQ(cb::count("testtest testastest"s, "test"s), 4);
    EXPECT_EQ(cb::count(u8"testtest testastest"s, u8"test"s), 4);
    EXPECT_EQ(cb::count(u"testtest testastest"s, u"test"s), 4);
    EXPECT_EQ(cb::count(U"testtest testastest"s, U"test"s), 4);

    EXPECT_EQ(cb::count(u8"tststststs"s, u8"tsts"s), 2);
}

TEST(cbcore_strings, subcompare) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_str = "źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_what_str = "ścieka"s;
    const auto test_what_vector_str = std::vector{"ścieka"s, "dżdżownicy"s};
    const auto test_what_set_str = std::set{"ścieka"s, "dżdżownicy"s};
    const auto test_what_uset_str = std::unordered_set{"ścieka"s, "dżdżownicy"s};

    EXPECT_TRUE(cb::sub_compare(test_text_str, test_what_str, 16));
    EXPECT_TRUE(cb::sub_compare(test_what_str, test_what_str, 0));
    EXPECT_TRUE(cb::sub_compare(test_text_str, test_what_vector_str, 16));
    EXPECT_TRUE(cb::sub_compare(test_text_str, test_what_vector_str, 36));
    EXPECT_TRUE(cb::sub_compare(test_text_str, test_what_set_str, 16));
    EXPECT_TRUE(cb::sub_compare(test_text_str, test_what_set_str, 36));
    EXPECT_TRUE(cb::sub_compare(test_text_str, test_what_uset_str, 16));
    EXPECT_TRUE(cb::sub_compare(test_text_str, test_what_uset_str, 36));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_str, 10));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_str, 0));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_str, test_text_str.length()));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_vector_str, 13));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_vector_str, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_set_str, 13));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_set_str, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_uset_str, 13));
    EXPECT_FALSE(cb::sub_compare(test_text_str, test_what_uset_str, 45));

    const auto test_text_utf8 = u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_what_utf8 = u8"ścieka"s;
    const auto test_what_vector_utf8 = std::vector{u8"ścieka"s, u8"dżdżownicy"s};
    const auto test_what_set_utf8 = std::set{u8"ścieka"s, u8"dżdżownicy"s};
    const auto test_what_uset_utf8 = std::unordered_set{u8"ścieka"s, u8"dżdżownicy"s};

    EXPECT_TRUE(cb::sub_compare(test_text_utf8, test_what_utf8, 16));
    EXPECT_TRUE(cb::sub_compare(test_what_utf8, test_what_utf8, 0));
    EXPECT_TRUE(cb::sub_compare(test_text_utf8, test_what_vector_utf8, 16));
    EXPECT_TRUE(cb::sub_compare(test_text_utf8, test_what_vector_utf8, 36));
    EXPECT_TRUE(cb::sub_compare(test_text_utf8, test_what_set_utf8, 16));
    EXPECT_TRUE(cb::sub_compare(test_text_utf8, test_what_set_utf8, 36));
    EXPECT_TRUE(cb::sub_compare(test_text_utf8, test_what_uset_utf8, 16));
    EXPECT_TRUE(cb::sub_compare(test_text_utf8, test_what_uset_utf8, 36));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_utf8, 10));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_utf8, 0));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_utf8, test_text_utf8.length()));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_vector_utf8, 13));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_vector_utf8, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_set_utf8, 13));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_set_utf8, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_uset_utf8, 13));
    EXPECT_FALSE(cb::sub_compare(test_text_utf8, test_what_uset_utf8, 45));

    const auto test_text_utf16 = u"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_what_utf16 = u"ścieka"s;
    const auto test_what_vector_utf16 = std::vector{u"ścieka"s, u"dżdżownicy"s};
    const auto test_what_set_utf16 = std::set{u"ścieka"s, u"dżdżownicy"s};
    const auto test_what_uset_utf16 = std::unordered_set{u"ścieka"s, u"dżdżownicy"s};

    EXPECT_TRUE(cb::sub_compare(test_text_utf16, test_what_utf16, 13));
    EXPECT_TRUE(cb::sub_compare(test_what_utf16, test_what_utf16, 0));
    EXPECT_TRUE(cb::sub_compare(test_text_utf16, test_what_vector_utf16, 13));
    EXPECT_TRUE(cb::sub_compare(test_text_utf16, test_what_vector_utf16, 30));
    EXPECT_TRUE(cb::sub_compare(test_text_utf16, test_what_set_utf16, 13));
    EXPECT_TRUE(cb::sub_compare(test_text_utf16, test_what_set_utf16, 30));
    EXPECT_TRUE(cb::sub_compare(test_text_utf16, test_what_uset_utf16, 13));
    EXPECT_TRUE(cb::sub_compare(test_text_utf16, test_what_uset_utf16, 30));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_utf16, 10));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_utf16, 0));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_utf16, test_text_utf16.length()));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_vector_utf16, 15));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_vector_utf16, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_set_utf16, 15));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_set_utf16, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_uset_utf16, 15));
    EXPECT_FALSE(cb::sub_compare(test_text_utf16, test_what_uset_utf16, 45));

    const auto test_text_utf32 = U"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_what_utf32 = U"ścieka"s;
    const auto test_what_vector_utf32 = std::vector{U"ścieka"s, U"dżdżownicy"s};
    const auto test_what_set_utf32 = std::set{U"ścieka"s, U"dżdżownicy"s};
    const auto test_what_uset_utf32 = std::unordered_set{U"ścieka"s, U"dżdżownicy"s};

    EXPECT_TRUE(cb::sub_compare(test_text_utf32, test_what_utf32, 13));
    EXPECT_TRUE(cb::sub_compare(test_what_utf32, test_what_utf32, 0));
    EXPECT_TRUE(cb::sub_compare(test_text_utf32, test_what_vector_utf32, 13));
    EXPECT_TRUE(cb::sub_compare(test_text_utf32, test_what_vector_utf32, 30));
    EXPECT_TRUE(cb::sub_compare(test_text_utf32, test_what_set_utf32, 13));
    EXPECT_TRUE(cb::sub_compare(test_text_utf32, test_what_set_utf32, 30));
    EXPECT_TRUE(cb::sub_compare(test_text_utf32, test_what_uset_utf32, 13));
    EXPECT_TRUE(cb::sub_compare(test_text_utf32, test_what_uset_utf32, 30));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_utf32, 10));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_utf32, 0));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_utf32, test_text_utf32.length()));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_vector_utf32, 15));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_vector_utf32, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_set_utf32, 15));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_set_utf32, 45));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_uset_utf32, 15));
    EXPECT_FALSE(cb::sub_compare(test_text_utf32, test_what_uset_utf32, 45));
}
