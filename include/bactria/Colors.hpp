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

#ifndef BACTRIA_COLORS_HPP
#   define BACTRIA_COLORS_HPP

namespace bactria
{
    namespace color
    {
        constexpr auto red = 0xFFFF0000u;

        // Taken from CASUS corporate design
        constexpr auto green = 0xFFA0E300u;
        constexpr auto green80 = 0xFFEEFFC6u;
        constexpr auto green60 = 0xFFDEFF8Eu;
        constexpr auto green40 = 0xFFCDFF55u;
        constexpr auto green125 = 0xFF78AA00u;
        constexpr auto green150 = 0xFF507200u;

        // Taken from HZDR corporate design
        constexpr auto blue = 0xFF005AA0u;
        constexpr auto blue80 = 0xFF2473ADu;
        constexpr auto blue60 = 0xFF6691C2u;
        constexpr auto blue40 = 0xFF9BB3D7u;
        constexpr auto blue20 = 0xFFCDD8ECu;

        // Taken from CASUS corporate design
        constexpr auto white = 0xFFFFFFFFu;
        constexpr auto white105 = 0xFFF2F2F2u;
        constexpr auto white115 = 0xFFD9D9D9u;
        constexpr auto white125 = 0xFFBFBFBFu;
        constexpr auto white135 = 0xFFA6A6A6u;
        constexpr auto white150 = 0xFF7F7F7Fu;

        // Taken from CASUS corporate design
        constexpr auto black = 0xFF000000u;
        constexpr auto black95 = 0xFF0D0D0Du;
        constexpr auto black85 = 0xFF262626u;
        constexpr auto black75 = 0xFF404040u;
        constexpr auto black65 = 0xFF595959u;
        constexpr auto black50 = white150;

        // Taken from CASUS corporate design
        constexpr auto blue_grey = 0xFF44546Au;
        constexpr auto blue_grey80 = 0xFFD6DCE5u;
        constexpr auto blue_grey60 = 0xFFADB9CAu;
        constexpr auto blue_grey40 = 0xFF8497B0u;
        constexpr auto blue_grey125 = 0xFF333F50u;
        constexpr auto blue_grey150 = 0xFF222A35u;

        constexpr auto blue_gray = blue_grey;
        constexpr auto blue_gray80 = blue_grey80;
        constexpr auto blue_gray60 = blue_grey60;
        constexpr auto blue_gray40 = blue_grey40;
        constexpr auto blue_gray125 = blue_grey125;
        constexpr auto blue_gray150 = blue_grey150;

        // Taken from CASUS corporate design
        constexpr auto dark_blue = 0xFF005096u;
        constexpr auto dark_blue80 = 0xFFB7DDFFu;
        constexpr auto dark_blue60 = 0xFF6FBCFFu;
        constexpr auto dark_blue40 = 0xFF279AFFu;
        constexpr auto dark_blue125 = 0xFF003C71u;
        constexpr auto dark_blue150 = 0xFF00284Bu;

        // Taken from CASUS corporate design
        constexpr auto turquoise = 0xFF00C3FFu;
        constexpr auto turquoise80 = 0xFFCCF3FFu;
        constexpr auto turquoise60 = 0xFF99E7FFu;
        constexpr auto turquoise40 = 0xFF66DBFFu;
        constexpr auto turquoise125 = 0xFF0092BFu;
        constexpr auto turquoise150 = 0xFF00617Fu;

        // Taken from HZDR corporate design
        constexpr auto orange = 0xFFF0781Eu;
        constexpr auto orange80 = 0xFFF39150u;
        constexpr auto orange60 = 0xFFF7Af7Cu;
        constexpr auto orange40 = 0xFFFBCBA8u;
        constexpr auto orange20 = 0xFFFDE6D4u;

        // Taken from HZDR corporate design
        constexpr auto dark_grey = 0xFF515151u;
        constexpr auto dark_gray = dark_grey;
        constexpr auto grey = 0xFF9C9C9Cu;
        constexpr auto gray = grey;
        constexpr auto light_grey = 0xFFB9B9B9u;
        constexpr auto light_gray = light_grey;
    }
}

#endif
