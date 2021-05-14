/* Copyright 2021 Jan Stephan
 *
 * Licensed under the EUPL, Version 1.2 or - as soon they will be approved by
 * the European Commission - subsequent versions of the EUPL (the “Licence”).
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at:
 *
 *     http://ec.europa.eu/idabc/eupl.html
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an “AS IS” basis, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  Licence permissions and limitations under the Licence.
 */

/**
 * \file Category.hpp
 * \brief The Category include file.
 *
 * This is bactria's include file for Categories. It should not be included on its own.
 */

#pragma once

#include <cstdint>
#include <string>

namespace bactria
{
    /**
     * \brief Defines a category.
     *
     * This class can be used for defining own categories. Categories can later be used for filtering out
     * Ranges and Events. Each category is defined by an unique \a id and a \a name.
     */
    class Category
    {
    public:
        /**
         * \brief The default constructor.
         *
         * This constructs a default Category with the ID \a 0 and the name \a BACTRIA_GENERIC_CATEGORY.
         */
        Category() = default;

        /**
         * \brief The constructor.
         *
         * This constructs a Category with the ID \a id and the name \a name.
         */
        Category(std::uint32_t id, std::string name)
        : m_id{id}, m_name{std::move(name)}
        {}

        /**
         * \brief The copy constructor.
         *
         * Constructs a category with the same properties as \a other. \a this and \a other will share the same name
         * and ID after construction.
         *
         * \param other The Category to copy from.
         */
        Category(Category const& other) = default;

        /**
         * \brief The copy assignment operator.
         *
         * Copies the properties of \a rhs into \a this. \a this and \a other will share the same name and ID after
         * the assignment.
         *
         * \param rhs The Category to copy from.
         */
        auto operator=(Category const& rhs) -> Category& = default;

        /**
         * \brief The move constructor.
         *
         * Constructs a category by moving \a other's properties into \a this. \a this will be identical to \a other's
         * state before the move. \a other will be in an undefined state after construction.
         *
         * \param other The Category to move into \a this.
         */
        Category(Category&& other) = default;

        /**
         * \brief The move assignment operator.
         *
         * Moves the properties of \a rhs into \a this. \a this will be identical to \a rhs's state before the move.
         * \a rhs will be in an undefined state after the assignment.
         *
         * \param rhs The Category to move into \a this.
         */
        auto operator=(Category&& rhs) -> Category& = default;

        /**
         * \brief The destructor.
         *
         * Destroys the contents of \a this. \a this will be in an undefined state after destruction.
         */
        ~Category() = default;

        /**
         * \brief The ID getter method.
         *
         * \return The ID assigned to \a this.
         */
        auto get_id() const noexcept -> std::uint32_t
        {
            return m_id;
        }

        /**
         * \brief The name getter method.
         *
         * \return The name assigned to \a this.
         */
        auto get_name() const noexcept -> std::string const&
        {
            return m_name;
        }

        /**
         * \brief The C string name getter method.
         *
         * \return The name assigned to \a this as C string.
         */
        auto get_c_name() const noexcept -> char const*
        {
            return m_name.c_str();
        }
    
    private:
        std::uint32_t m_id{0u}; ///< The identifier of the category. Different categories require different identifiers.
        std::string m_name{"BACTRIA_GENERIC_CATEGORY"};
    };
}

