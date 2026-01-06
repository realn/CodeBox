//
// Created by noname on 2.01.2026.
//

#include <vector>
#include <set>
#include <unordered_set>
#include <list>

#include <gtest/gtest.h>

import realn.codebox.core;

TEST(cbcore_strings, conversion) {
    using namespace std::string_literals;

    //simple cast
    EXPECT_EQ(realn::cb::cast_string_to_u8("some text"), std::u8string{u8"some text"});
    EXPECT_EQ(realn::cb::cast_u8_to_string(u8"some text"), std::string{"some text"});

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

template<class string_type>
void test_sub_compare(const string_type &test_text, const string_type &test_what1, const string_type &test_what2,
                      const std::size_t correct_pos1, const std::size_t correct_pos2) {
    using namespace realn;
    const auto test_what_vector = std::vector{test_what1, test_what2};
    const auto test_what_set = std::set{test_what1, test_what2};
    const auto test_what_uset = std::unordered_set{test_what1, test_what2};

    const auto correct_positions_multi = std::unordered_set{
        correct_pos1, correct_pos2
    };

    for (auto pos = std::size_t{0}; pos < test_text.length(); pos++) {
        SCOPED_TRACE(std::format("Current Pos: {}", pos));
        if (correct_pos1 == pos) {
            EXPECT_TRUE(cb::sub_compare(test_text, test_what1, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare(test_text, test_what1, pos));
        }
        if (correct_positions_multi.contains(pos)) {
            EXPECT_TRUE(cb::sub_compare(test_text, test_what_vector, pos));
            EXPECT_TRUE(cb::sub_compare(test_text, test_what_set, pos));
            EXPECT_TRUE(cb::sub_compare(test_text, test_what_uset, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare(test_text, test_what_vector, pos));
            EXPECT_FALSE(cb::sub_compare(test_text, test_what_set, pos));
            EXPECT_FALSE(cb::sub_compare(test_text, test_what_uset, pos));
        }
    }
}

TEST(cbcore_strings, subcompare) {
    using namespace std::string_literals;

    {
        SCOPED_TRACE("while sub_compare - str testing.");
        test_sub_compare("źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         "ścieka"s, "dżdżownicy"s, 16, 36);
    }

    {
        SCOPED_TRACE("while sub_compare - utf8 testing.");
        test_sub_compare(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         u8"ścieka"s, u8"dżdżownicy"s, 16, 36);
    }

    {
        SCOPED_TRACE("while sub_compare - utf16 testing.");
        test_sub_compare(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         u"ścieka"s, u"dżdżownicy"s, 13, 30);
    }

    {
        SCOPED_TRACE("while sub_compare - utf32 testing.");
        test_sub_compare(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         U"ścieka"s, U"dżdżownicy"s, 13, 30);
    }
}

template<class string_type>
void test_sub_compare_from_back(const string_type &test_text, const string_type &test_what1,
                                const std::size_t correct_pos1) {
    using namespace realn;

    for (auto pos = std::size_t{0}; pos < test_text.length(); pos++) {
        SCOPED_TRACE(std::format("Current Pos: {}", pos));
        if (correct_pos1 == pos) {
            EXPECT_TRUE(cb::sub_compare_from_back(test_text, test_what1, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare_from_back(test_text, test_what1, pos));
        }
    }
}

TEST(cbcore_strings, subcompare_from_back) {
    using namespace std::string_literals;

    {
        SCOPED_TRACE("while sub_compare_from_back - str testing.");
        test_sub_compare_from_back("źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   "ścieka"s, 39);
    }

    {
        SCOPED_TRACE("while sub_compare_from_back - utf8 testing.");
        test_sub_compare_from_back(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   u8"ścieka"s, 39);
    }

    {
        SCOPED_TRACE("while sub_compare_from_back - utf16 testing.");
        test_sub_compare_from_back(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   u"ścieka"s, 33);
    }

    {
        SCOPED_TRACE("while sub_compare_from_back - utf32 testing.");
        test_sub_compare_from_back(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   U"ścieka"s, 33);
    }
}

template<class string_type>
void test_sub_compare_from_word_back(const string_type &test_text, const string_type &test_what1,
                                     const std::size_t correct_pos1) {
    using namespace realn;

    for (auto pos = std::size_t{0}; pos < test_text.length(); pos++) {
        SCOPED_TRACE(std::format("Current Pos: {}", pos));
        if (correct_pos1 == pos) {
            EXPECT_TRUE(cb::sub_compare_from_word_back(test_text, test_what1, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare_from_word_back(test_text, test_what1, pos));
        }
    }
}

TEST(cbcore_strings, subcompare_from_word_back) {
    using namespace std::string_literals;

    {
        SCOPED_TRACE("while sub_compare_from_word_back - str testing.");
        test_sub_compare_from_word_back("źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        "ścieka"s, 23);
    }

    {
        SCOPED_TRACE("while sub_compare_from_word_back - utf8 testing.");
        test_sub_compare_from_word_back(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        u8"ścieka"s, 23);
    }

    {
        SCOPED_TRACE("while sub_compare_from_word_back - utf16 testing.");
        test_sub_compare_from_word_back(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        u"ścieka"s, 19);
    }

    {
        SCOPED_TRACE("while sub_compare_from_word_back - utf32 testing.");
        test_sub_compare_from_word_back(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        U"ścieka"s, 19);
    }
}

template<class string_type, class string_container_type>
void test_sub_find_container(const std::string &test_name, const string_type &test_text,
                             const string_container_type &test_list) {
    using namespace realn;

    SCOPED_TRACE(test_name);
    size_t list_index = 0;
    for (const auto &[list, correct_pos]: test_list) {
        SCOPED_TRACE(std::format("list_index: {}", list_index++));
        const auto pos = cb::sub_find(test_text, list);
        EXPECT_EQ(pos, correct_pos);
    }
}

template<class string_type = std::u8string, class from_u8_func_type>
void test_sub_find_string_type(const std::string &test_name,
                               const std::array<std::size_t, 4> &vec_pos,
                               const std::array<std::size_t, 4> &set_pos,
                               const std::array<std::size_t, 4> &uset_pos,
                               from_u8_func_type from_u8) {
    using namespace std::string_literals;

    SCOPED_TRACE(test_name);

    using vector_item_type = std::pair<std::vector<string_type>, std::size_t>;
    using set_item_type = std::pair<std::set<string_type>, std::size_t>;
    using uset_item_type = std::pair<std::unordered_set<string_type>, std::size_t>;

    const auto test_text = from_u8(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s);
    const auto test_find_vec_list = std::list<vector_item_type>{
        {{from_u8(u8"trawy"s), from_u8(u8"ka w s"s), from_u8(u8"dżdżownicy"s), from_u8(u8"ło trawy"s)}, vec_pos[0]},
        {{from_u8(u8"ka w s"s), from_u8(u8"trawy"s), from_u8(u8"dżdżownicy"s), from_u8(u8"ło trawy"s)}, vec_pos[1]},
        {{from_u8(u8"dżdżownicy"s), from_u8(u8"trawy"s), from_u8(u8"ka w s"s), from_u8(u8"ło trawy"s)}, vec_pos[2]},
        {{from_u8(u8"ło trawy"s), from_u8(u8"dżdżownicy"s), from_u8(u8"trawy"s), from_u8(u8"ka w s"s)}, vec_pos[3]},
    };
    const auto test_find_set_list = std::list<set_item_type>{
        {{from_u8(u8"trawy"s), from_u8(u8"ka w s"s), from_u8(u8"dżdżownicy"s), from_u8(u8"ło trawy"s)}, set_pos[0]},
        {{from_u8(u8"ka w s"s), from_u8(u8"trawy"s), from_u8(u8"dżdżownicy"s), from_u8(u8"ło trawy"s)}, set_pos[1]},
        {{from_u8(u8"dżdżownicy"s), from_u8(u8"trawy"s), from_u8(u8"ka w s"s), from_u8(u8"ło trawy"s)}, set_pos[2]},
        {{from_u8(u8"ło trawy"s), from_u8(u8"dżdżownicy"s), from_u8(u8"trawy"s), from_u8(u8"ka w s"s)}, set_pos[3]},
    };
    const auto test_find_uset_list = std::list<uset_item_type>{
        {{from_u8(u8"trawy"s), from_u8(u8"ka w s"s), from_u8(u8"dżdżownicy"s), from_u8(u8"ło trawy"s)}, uset_pos[0]},
        {{from_u8(u8"ka w s"s), from_u8(u8"trawy"s), from_u8(u8"dżdżownicy"s), from_u8(u8"ło trawy"s)}, uset_pos[1]},
        {{from_u8(u8"dżdżownicy"s), from_u8(u8"trawy"s), from_u8(u8"ka w s"s), from_u8(u8"ło trawy"s)}, uset_pos[2]},
        {{from_u8(u8"ło trawy"s), from_u8(u8"dżdżownicy"s), from_u8(u8"trawy"s), from_u8(u8"ka w s"s)}, uset_pos[3]},
    };

    test_sub_find_container("std::vector", test_text, test_find_vec_list);
    test_sub_find_container("std::set", test_text, test_find_set_list);
    test_sub_find_container("std::unordered_set", test_text, test_find_uset_list);
}

TEST(cbcore_strings, sub_find) {
    using namespace std::string_literals;
    using namespace realn;

    constexpr auto str_vec_pos = std::array<std::size_t, 4>{6, 6, 6, 6};
    constexpr auto str_set_pos = std::array<std::size_t, 4>{6, 6, 6, 6};
    constexpr auto str_uset_pos = std::array<std::size_t, 4>{6, 6, 6, 6};

    constexpr auto utf8_vec_pos = std::array<std::size_t, 4>{6, 6, 6, 6};
    constexpr auto utf8_set_pos = std::array<std::size_t, 4>{6, 6, 6, 6};
    constexpr auto utf8_uset_pos = std::array<std::size_t, 4>{6, 6, 6, 6};

    constexpr auto utf16_vec_pos = std::array<std::size_t, 4>{4, 4, 4, 4};
    constexpr auto utf16_set_pos = std::array<std::size_t, 4>{4, 4, 4, 4};
    constexpr auto utf16_uset_pos = std::array<std::size_t, 4>{4, 4, 4, 4};

    constexpr auto utf32_vec_pos = std::array<std::size_t, 4>{4, 4, 4, 4};
    constexpr auto utf32_set_pos = std::array<std::size_t, 4>{4, 4, 4, 4};
    constexpr auto utf32_uset_pos = std::array<std::size_t, 4>{4, 4, 4, 4};

    test_sub_find_string_type<std::string>("std::string",
                                           str_vec_pos,
                                           str_set_pos,
                                           str_uset_pos,
                                           cb::cast_u8_to_string);

    test_sub_find_string_type<std::u8string>("std::u8string",
                                             utf8_vec_pos,
                                             utf8_set_pos,
                                             utf8_uset_pos,
                                             [](const std::u8string &text) { return text; });

    test_sub_find_string_type<std::u16string>("std::u16string",
                                              utf16_vec_pos,
                                              utf16_set_pos,
                                              utf16_uset_pos,
                                              [](const std::u8string &text) { return cb::utf_convert_to_u16(text); });

    test_sub_find_string_type<std::u32string>("std::u32string",
                                              utf32_vec_pos,
                                              utf32_set_pos,
                                              utf32_uset_pos,
                                              [](const std::u8string &text) { return cb::utf_convert_to_u32(text); });
}
