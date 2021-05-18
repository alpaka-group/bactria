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
 * \file Colors.hpp
 * \brief bactria's color include file.
 *
 * This is bactria's color include file. It contains a small color palette in ARGB format.
 * Most colors have numerical suffixes: values lower than 100 denote a lighter color, values larger than 100 a darker
 * color.
 *
 * This file should not be included directly, it is already pulled in by bactria.hpp.
 */

#pragma once

namespace bactria
{
    namespace color
    {
        // Taken (with permission) from Helmholtz corporate design
        constexpr auto helmholtz_blue = 0xFF005AA0u;
        constexpr auto helmholtz_dark_blue = 0xFF0A2D6Eu;
        constexpr auto helmholtz_green = 0xFF8Cb423u;
        constexpr auto helmholtz_grey = 0xFF5A696Eu;
        constexpr auto helmholtz_gray = helmholtz_grey;
        constexpr auto helmholtz_ruby = 0xFFA0235Au;
        constexpr auto helmholtz_red = 0xFFD23264u;
        constexpr auto helmholtz_orange = 0xFF0781Eu;
        constexpr auto helmholtz_yellow = 0xFFFFD228u;
        constexpr auto helmholtz_turquoise = 0xFF50C8AAu;
        constexpr auto helmholtz_dark_cyan = 0xFF326469u;

        // Taken (with permission) from HZDR corporate design
        constexpr auto hzdr_blue = helmholtz_blue;
        constexpr auto hzdr_blue80 = 0xFF2473ADu;
        constexpr auto hzdr_blue60 = 0xFF6691C2u;
        constexpr auto hzdr_blue40 = 0xFF9BB3D7u;
        constexpr auto hzdr_blue20 = 0xFFCDD8ECu;
        constexpr auto hzdr_orange = helmholtz_orange;
        constexpr auto hzdr_orange80 = 0xFFF39150u;
        constexpr auto hzdr_orange60 = 0xFFF7Af7Cu;
        constexpr auto hzdr_orange40 = 0xFFFBCBA8u;
        constexpr auto hzdr_orange20 = 0xFFFDE6D4u;
        constexpr auto hzdr_dark_grey = 0xFF515151u;
        constexpr auto hzdr_dark_gray = hzdr_dark_grey;
        constexpr auto hzdr_grey = 0xFF9C9C9Cu;
        constexpr auto hzdr_gray = hzdr_grey;
        constexpr auto hzdr_light_grey = 0xFFB9B9B9u;
        constexpr auto hzdr_light_gray = hzdr_light_grey;

        // Taken (with permission) from CASUS corporate design
        constexpr auto casus_black = 0xFF000000u;
        constexpr auto casus_black95 = 0xFF0D0D0Du;
        constexpr auto casus_black85 = 0xFF262626u;
        constexpr auto casus_black75 = 0xFF404040u;
        constexpr auto casus_black65 = 0xFF595959u;
        constexpr auto casus_black50 = 0xFF7F7F7Fu;
        constexpr auto casus_blue = 0xFF4472C4u;
        constexpr auto casus_blue20 = 0xFFDAE3F3u;
        constexpr auto casus_blue40 = 0xFFB4C7E7u;
        constexpr auto casus_blue60 = 0xFF8FAADCu;
        constexpr auto casus_blue125 = 0xFF2F5597u;
        constexpr auto casus_blue150 = 0xFF203864u;
        constexpr auto casus_blue_grey = 0xFF44546Au;
        constexpr auto casus_blue_grey20 = 0xFFD6DCE5u;
        constexpr auto casus_blue_grey40 = 0xFFADB9CAu;
        constexpr auto casus_blue_grey60 = 0xFF8497B0u;
        constexpr auto casus_blue_grey125 = 0xFF333F50u;
        constexpr auto casus_blue_grey150 = 0xFF222A35u;
        constexpr auto casus_blue_gray = casus_blue_grey;
        constexpr auto casus_blue_gray20 = casus_blue_grey20;
        constexpr auto casus_blue_gray40 = casus_blue_grey40;
        constexpr auto casus_blue_gray60 = casus_blue_grey60;
        constexpr auto casus_blue_gray125 = casus_blue_grey125;
        constexpr auto casus_blue_gray150 = casus_blue_grey150;
        constexpr auto casus_dark_blue = 0xFF005096u;
        constexpr auto casus_dark_blue20 = 0xFFB7DDFFu;
        constexpr auto casus_dark_blue40 = 0xFF6FBCFFu;
        constexpr auto casus_dark_blue60 = 0xFF279AFFu;
        constexpr auto casus_dark_blue125 = 0xFF003C71u;
        constexpr auto casus_dark_blue150 = 0xFF00284Bu;
        constexpr auto casus_green = 0xFFA0E300u;
        constexpr auto casus_green60 = 0xFFCDFF55u;
        constexpr auto casus_green40 = 0xFFDEFF8Eu;
        constexpr auto casus_green20 = 0xFFEEFFC6u;
        constexpr auto casus_green125 = 0xFF78AA00u;
        constexpr auto casus_green150 = 0xFF507200u;
        constexpr auto casus_green_alt = 0xFF70AD47u;
        constexpr auto casus_green_alt20 = 0xFFE2F0D9u;
        constexpr auto casus_green_alt40 = 0xFFC5E0B4u;
        constexpr auto casus_green_alt60 = 0xFFA9D18Eu;
        constexpr auto casus_green_alt125 = 0xFF548235u;
        constexpr auto casus_green_alt150 = 0xFF203864u;
        constexpr auto casus_grey = 0xFFA1A1A1u;
        constexpr auto casus_grey20 = 0xFFECECECu;
        constexpr auto casus_grey40 = 0xFFD9D9D9u;
        constexpr auto casus_grey60 = 0xFFC7C7C7u;
        constexpr auto casus_grey125 = 0xFF797979u;
        constexpr auto casus_grey150 = 0xFF515151u;
        constexpr auto casus_light_grey = 0xFFE7E6E6u;
        constexpr auto casus_light_grey110 = 0xFFD0CECEu;
        constexpr auto casus_light_grey125 = 0xFFAFABABu;
        constexpr auto casus_light_grey150 = 0xFF767171u;
        constexpr auto casus_light_grey175 = 0xFF3B3838u;
        constexpr auto casus_light_grey190 = 0xFF181717u;
        constexpr auto casus_turquoise = 0xFF00C3FFu;
        constexpr auto casus_turquoise20 = 0xFFCCF3FFu;
        constexpr auto casus_turquoise40 = 0xFF99E7FFu;
        constexpr auto casus_turquoise60 = 0xFF66DBFFu;
        constexpr auto casus_turquoise125 = 0xFF0092BFu;
        constexpr auto casus_turquoise150 = 0xFF00617Fu;
        constexpr auto casus_white = 0xFFFFFFFFu;
        constexpr auto casus_white105 = 0xFFF2F2F2u;
        constexpr auto casus_white115 = 0xFFD9D9D9u;
        constexpr auto casus_white125 = 0xFFBFBFBFu;
        constexpr auto casus_white135 = 0xFFA6A6A6u;
        constexpr auto casus_white150 = 0xFF7F7F7Fu;

        // bactria uses Helmholtz' palette internally
        constexpr auto bactria_blue = helmholtz_blue;
        constexpr auto bactria_cyan = helmholtz_dark_cyan;
        constexpr auto bactria_dark_blue = helmholtz_dark_blue;
        constexpr auto bactria_green = helmholtz_green;
        constexpr auto bactria_grey = helmholtz_grey;
        constexpr auto bactria_gray = helmholtz_gray;
        constexpr auto bactria_orange = helmholtz_orange;
        constexpr auto bactria_red = helmholtz_red;
        constexpr auto bactria_ruby = helmholtz_ruby;
        constexpr auto bactria_turquoise = helmholtz_turquoise;
        constexpr auto bactria_yellow = helmholtz_yellow;

        // A few HTML standard colors
        constexpr auto black = 0xFF000000u;
        constexpr auto blue = 0xFF0000FFu;
        constexpr auto brown = 0xFFA52A2Au;
        constexpr auto crimson = 0xFFDC143Cu;
        constexpr auto cyan = 0xFF00FFFFu;
        constexpr auto dark_blue = 0xFF00008Bu;
        constexpr auto dark_cyan = 0xFF008B8Bu;
        constexpr auto dark_gray = 0xFFA9A9A9u;
        constexpr auto dark_grey = 0xFFA9A9A9u;
        constexpr auto dark_green = 0xFF006400u;
        constexpr auto dark_magenta = 0xFF8B008Bu;
        constexpr auto dark_orange = 0xFFFF8C00u;
        constexpr auto dark_red = 0xFF8B0000u;
        constexpr auto dark_violet = 0xFF9400D3u;
        constexpr auto dark_turquoise = 0xFF00CED1u;
        constexpr auto gold = 0xFFFFD700u;
        constexpr auto gray = 0xFF808080u;
        constexpr auto green = 0xFF008000u;
        constexpr auto grey = 0xFF808080u;
        constexpr auto light_blue = 0xFFADD8E6u;
        constexpr auto light_cyan = 0xFFE0FFFFu;
        constexpr auto light_gray = 0xFFD3D3D3u;
        constexpr auto light_grey = 0xFFD3D3D3u;
        constexpr auto light_green = 0xFF90EE90u;
        constexpr auto light_yellow = 0xFFFFFFE0u;
        constexpr auto lime = 0xFF00FF00u;
        constexpr auto magenta = 0xFFFF00FFu;
        constexpr auto maroon = 0xFF800000u;
        constexpr auto medium_blue = 0xFF0000CDu;
        constexpr auto medium_purple = 0xFF9370DBu;
        constexpr auto medium_turquoise = 0xFF48D1CCu;
        constexpr auto olive = 0xFF808000u;
        constexpr auto orange = 0xFFFFA500u;
        constexpr auto pink = 0xFFFFC0CBu;
        constexpr auto purple = 0xFF800080u;
        constexpr auto red = 0xFFFF0000u;
        constexpr auto silver = 0xFFC0C0C0u;
        constexpr auto turquoise = 0xFF40E0D0u;
        constexpr auto violet = 0xFFEE82EEu;
        constexpr auto yellow = 0xFFFFFF00u;
        constexpr auto white = 0xFFFFFFFFu;
    } // namespace color
} // namespace bactria
