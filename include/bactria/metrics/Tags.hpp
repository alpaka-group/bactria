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
 * \file Tags.hpp
 * \brief Tag definitions.
 *
 * This file defines a number of tags that can be used to add more details to a Sector.
 * It should not be included directly by the user.
 */

#pragma once

namespace bactria
{
    namespace metrics
    {
        /**
         * \brief The generic tag.
         * \ingroup bactria_metrics_user
         *
         * Used for defining a generic Sector.
         */
        struct Generic
        {
            /**
             * Internal value of the tag which is supplied to the plugin. Note that this may change between bactria
             * without further announcement. Users are strongly advised to never rely directly on the value of this
             * tag.
             */
            static constexpr auto value = 1u;
        };

        /**
         * \brief The function tag.
         * \ingroup bactria_metrics_user
         *
         * Used for defining a Sector that instruments a function.
         */
        struct Function
        {
            /**
             * Internal value of the tag which is supplied to the plugin. Note that this may change between bactria
             * without further announcement. Users are strongly advised to never rely directly on the value of this
             * tag.
             */
            static constexpr auto value = 2u;
        };

        /**
         * \brief The loop tag.
         * \ingroup bactria_metrics_user
         *
         * Used for defining a Sector that instruments an entire loop.
         * \sa Body
         */
        struct Loop
        {
            /**
             * Internal value of the tag which is supplied to the plugin. Note that this may change between bactria
             * without further announcement. Users are strongly advised to never rely directly on the value of this
             * tag.
             */
            static constexpr auto value = 3u;
        };

        /**
         * \brief The body tag.
         * \ingroup bactria_metrics_user
         *
         * Used for defining a Sector that instruments a (loop) body. This will result in separate
         * instrumentation paths for each (loop) iteration of the Sector.
         * \sa Loop
         */
        struct Body
        {
            /**
             * Internal value of the tag which is supplied to the plugin. Note that this may change between bactria
             * without further announcement. Users are strongly advised to never rely directly on the value of this
             * tag.
             */
            static constexpr auto value = 4u;
        };
    } // namespace metrics
} // namespace bactria
