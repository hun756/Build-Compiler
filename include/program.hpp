#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include <string>
#include <iostream>
#include <any>

#include "helper/string_helper.hpp"
#include "helper/var.hpp"

namespace Compiler
{

    enum class SytaxKind
    {
        NumberToken,
        WhiteSpaceToken,
        PlusToken,
        MinusToken,
        StarToken,
        SlahToken,
        OpenParanthesisToken,
        CloseParanthesisToken,
        BadToken,
        EndOfFileToken
    };


    std::ostream& operator<<(std::ostream& os, const SytaxKind sk)
    {
        switch(sk)
        {
            case SytaxKind::BadToken: {
                os << "BadToken";
                break;
            }
            
            case SytaxKind::CloseParanthesisToken : {
                os << "CloseParanthesisToken";
                break;
            }
            case SytaxKind::EndOfFileToken : {
                os << "EndOfFileToken";
                break;
            }
            case SytaxKind::MinusToken : {
                os << "MinusToken";
                break;
            }
            case SytaxKind::NumberToken : {
                os << "NumberToken";
                break;
            }
            case SytaxKind::OpenParanthesisToken : {
                os << "OpenParanthesisToken";
                break;
            }
            case SytaxKind::PlusToken : {
                os << "PlusToken";
                break;
            }
            case SytaxKind::SlahToken : {
                os << "SlahToken";
                break;
            }
            case SytaxKind::StarToken : {
                os << "StarToken";
                break;
            }
            case SytaxKind::WhiteSpaceToken : {
                os << "WhiteSpaceToken";
                break;
            }
        }
        return os;
    }

    class SyntaxToken
    {
    public:
        template <typename T>
        SyntaxToken(SytaxKind kind, int position, std::string text, T value)
            : kind(kind), position(position), text(text), value(value)
        {
        }

    public:
        SytaxKind kind;
        int position;
        std::string text;
        std::any value;
    };

    class Lexer
    {
    public:
        Lexer(std::string text)
            : text(text)
        {
        }

        Var<char> current {
            [this](char ch) {},
            [this]() -> char
            {
                if (position >= text.length())
                {
                    return '\0';
                }

                return text[position];
            }};

        SyntaxToken nextToken()
        {
            if (position >= text.length())
                return {SytaxKind::EndOfFileToken, position, "\0", nullptr};

            if (isdigit(current))
            {
                auto start = position;
                while (isdigit(current))
                {
                    this->next();
                }

                auto length = position - start;
                auto _text = text.substr(start, length);
                int val = Helper::String::atoi(_text);

                return {SytaxKind::NumberToken, start, _text, val};
            }

            if (isspace(current))
            {
                auto start = position;
                while (isspace(current))
                {
                    this->next();
                }

                auto length = position - start;
                auto _text = text.substr(start, length);
                int val = Helper::String::atoi(_text);

                return {SytaxKind::WhiteSpaceToken, start, _text, val};
            }

            switch (current)
            {
                case '+':
                {
                    return {SytaxKind::PlusToken, ++position, "+", nullptr};
                }

                case '-':
                {
                    return {SytaxKind::MinusToken, ++position, "", nullptr};
                }

                case '*':
                {
                    return {SytaxKind::StarToken, ++position, "*", nullptr};
                }

                case '/':
                {
                    return {SytaxKind::SlahToken, ++position, "/", nullptr};
                }

                case '(':
                {
                    return {SytaxKind::OpenParanthesisToken, ++position, "(", nullptr};
                }

                case ')':
                {
                    return {SytaxKind::CloseParanthesisToken, ++position, ")", nullptr};
                }

                default:
                {
                    return {SytaxKind::BadToken, ++position, text.substr(position - 1, 1), nullptr};
                }
            }
        }

    private:
        inline void next()
        {
            ++position;
        }

    private:
        int position {0};
        const std::string text;
    };

    class Program
    {
    public:
        static void Main(std::vector<std::string> args)
        {
            while (true)
            {
                std::cout << "> ";

                std::string line{""};
                std::getline(std::cin >> std::ws, line);

                if (Helper::String::isNullOrWhiteSpace(line))
                    return;

                auto lexer = Lexer(line);
                while (true)
                {
                    auto token = lexer.nextToken();
                    std::cout << token.kind << '\n';
                    if (token.kind == SytaxKind::EndOfFileToken)
                        break;

                    std::cout << token.kind << " : "  << token.text << '\n';
                    if (token.value.has_value())
                        // std::cout << std::any_cast<std::string>(token.value);
                    
                    std::cout << '\n';
                }
            }
        }
    };

} ///< namespace Compiler

#endif /* end of include guard :  PROGRAM_HPP */
