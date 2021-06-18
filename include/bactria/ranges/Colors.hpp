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
 * \brief Color definitions.
 *
 * This is bactria's color include file. It contains a small color palette in ARGB format.
 * Most colors have numerical suffixes: values lower than 100 denote a lighter color, values larger than 100 a darker
 * color.
 *
 * This file should not be included directly by the user..
 */

#pragma once

namespace bactria
{
    namespace ranges
    {
        namespace color
        {
            /**
             * \defgroup colors Predefined colors
             * \ingroup bactria_ranges_user
             * \{
             */

            /**
             * \defgroup helmholtz Helmholtz corporate design colors
             *
             * These colors were taken (with permission) from the [Helmholtz](https://www.helmholtz.de) corporate
             * design. They are mainly intended for members of the Helmholtz association who want their profiler
             * output to match the corporate design of their presentations, websites or documents.
             *
             * \{
             */

            /**
             * The color "Helmholtz Blue":
             * <span style="background-color: #005AA0;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             * \sa hzdr_blue
             */
            constexpr auto helmholtz_blue = 0xFF005AA0u;

            /**
             * The color "Helmholtz Dark Blue":
             * <span style="background-color: #0A2D6E;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_dark_blue = 0xFF0A2D6Eu;

            /**
             * The color "Helmholtz Green":
             * <span style="background-color: #8CB423;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_green = 0xFF8CB423u;

            /**
             * The color "Helmholtz Grey":
             * <span style="background-color: #5A696E;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_grey = 0xFF5A696Eu;

            /**
             * The color "Helmholtz Gray". This an alias for the color "Helmholtz Grey".
             * \sa helmholtz_grey
             */
            constexpr auto helmholtz_gray = helmholtz_grey;

            /**
             * The color "Helmholtz Ruby":
             * <span style="background-color: #A0235A;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_ruby = 0xFFA0235Au;

            /**
             * The color "Helmholtz Red":
             * <span style="background-color: #D23264;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_red = 0xFFD23264u;

            /**
             * The color "Helmholtz Orange":
             * <span style="background-color: #F0781E;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             * \sa hzdr_orange
             */
            constexpr auto helmholtz_orange = 0xFFF0781Eu;

            /**
             * The color "Helmholtz Yellow":
             * <span style="background-color: #FFD228;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_yellow = 0xFFFFD228u;

            /**
             * The color "Helmholtz Turquoise":
             * <span style="background-color: #50C8AA;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_turquoise = 0xFF50C8AAu;

            /**
             * The color "Helmholtz Dark Cyan":
             * <span style="background-color: #326469;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto helmholtz_dark_cyan = 0xFF326469u;

            /**
             * \}
             */ // Doxygen group "helmholtz"

            /**
             * \defgroup hzdr HZDR corporate design colors
             *
             * These colors were taken (with permission) from the [HZDR](https://www.hzdr.de) corporate design. They
             * are mainly intended for members of the Helmholtz-Zentrum Dresden-Rossendorf who want their profiler
             * output to match the corporate design of their presentations, websites or documents.
             *
             * \{
             */
            /**
             * The color "HZDR Blue":
             * <span style="background-color: #005AA0;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_blue = 0xFF005AA0u;

            /**
             * The color "HZDR Blue 80%":
             * <span style="background-color: #2473AD;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_blue80 = 0xFF2473ADu;

            /**
             * The color "HZDR Blue 60%":
             * <span style="background-color: #6691C2;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_blue60 = 0xFF6691C2u;

            /**
             * The color "HZDR Blue 40%":
             * <span style="background-color: #9BB3D7;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_blue40 = 0xFF9BB3D7u;

            /**
             * The color "HZDR Blue 20%":
             * <span style="background-color: #CDD8EC;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_blue20 = 0xFFCDD8ECu;

            /**
             * The color "HZDR Orange":
             *  <span style="background-color: #F0781E;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_orange = 0xFFF0781Eu;

            /**
             * The color "HZDR Orange 80%":
             * <span style="background-color: #F39150;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_orange80 = 0xFFF39150u;

            /**
             * The color "HZDR Orange 60%":
             * <span style="background-color: #F7AF7C;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_orange60 = 0xFFF7AF7Cu;

            /**
             * The color "HZDR Orange 40%":
             * <span style="background-color: #FBCBA8;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_orange40 = 0xFFFBCBA8u;

            /**
             * The color "HZDR Orange 20%":
             * <span style="background-color: #FDE6D4;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_orange20 = 0xFFFDE6D4u;

            /**
             * The color "HZDR Dark Grey":
             * <span style="background-color: #515151;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_dark_grey = 0xFF515151u;

            /**
             * The color "HZDR Dark Gray". This is an alias for the color "HZDR Dark Grey".
             * \sa hzdr_dark_grey
             */
            constexpr auto hzdr_dark_gray = hzdr_dark_grey;

            /**
             * The color "HZDR Grey":
             * <span style="background-color: #9C9C9C;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_grey = 0xFF9C9C9Cu;

            /**
             * The color "HZDR Gray". This is an alias for the color "HZDR Grey".
             * \sa hzdr_grey
             */
            constexpr auto hzdr_gray = hzdr_grey;

            /**
             * The color "HZDR Light Grey":
             * <span style="background-color: #B9B9B9;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto hzdr_light_grey = 0xFFB9B9B9u;

            /**
             * The color "HZDR Light Gray". This is an alias for the color "HZDR Light Grey".
             * \sa hzdr_light_grey
             */
            constexpr auto hzdr_light_gray = hzdr_light_grey;

            /**
             * \}
             */ // Doxygen group "hzdr"

            /**
             * \defgroup casus CASUS corporate design colors
             *
             * These colors were taken (with permission) from the [CASUS](https://www.casus.science) corporate design.
             * They are mainly intended for members of the Center of Advanced Systems Understanding who want their
             * profiler output to match the corporate design of their presentations, websites or documents.
             *
             * \{
             */
            /**
             * The color "CASUS Black":
             * <span style="background-color: #000000;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_black = 0xFF000000u;

            /**
             * The color "CASUS Black 95%":
             * <span style="background-color: #0D0D0D;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_black95 = 0xFF0D0D0Du;

            /**
             * The color "CASUS Black 85%":
             * <span style="background-color: #262626;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_black85 = 0xFF262626u;

            /**
             * The color "CASUS Black 75%":
             * <span style="background-color: #404040;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_black75 = 0xFF404040u;

            /**
             * The color "CASUS Black 65%":
             * <span style="background-color: #595959;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_black65 = 0xFF595959u;

            /**
             * The color "CASUS Black 50%":
             * <span style="background-color: #7F7F7F;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_black50 = 0xFF7F7F7Fu;

            /**
             * The color "CASUS Blue":
             * <span style="background-color: #4472C4;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue = 0xFF4472C4u;

            /**
             * The color "CASUS Blue 20%":
             * <span style="background-color: #DAE3F3;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue20 = 0xFFDAE3F3u;

            /**
             * The color "CASUS Blue 40%":
             * <span style="background-color: #B4C7E7;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue40 = 0xFFB4C7E7u;

            /**
             * The color "CASUS Blue 60%":
             * <span style="background-color: #8FAADC;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue60 = 0xFF8FAADCu;

            /**
             * The color "CASUS Blue 125%":
             * <span style="background-color: #2F5597;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue125 = 0xFF2F5597u;

            /**
             * The color "CASUS Blue 150%":
             * <span style="background-color: #203864;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue150 = 0xFF203864u;

            /**
             * The color "CASUS Blue Grey":
             * <span style="background-color: #44546A;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue_grey = 0xFF44546Au;

            /**
             * The color "CASUS Blue Grey 20%":
             * <span style="background-color: #D6DCE5;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue_grey20 = 0xFFD6DCE5u;

            /**
             * The color "CASUS Blue Grey 40%":
             * <span style="background-color: #ADB9CA;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue_grey40 = 0xFFADB9CAu;

            /**
             * The color "CASUS Blue Grey 60%":
             * <span style="background-color: #8497B0;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue_grey60 = 0xFF8497B0u;

            /**
             * The color "CASUS Blue Grey 125%":
             * <span style="background-color: #333F50;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue_grey125 = 0xFF333F50u;

            /**
             * The color "CASUS Blue Grey 150%":
             * <span style="background-color: #222A35;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_blue_grey150 = 0xFF222A35u;

            /**
             * The color "CASUS Blue Gray". This is an alias for the color "CASUS Blue Grey".
             * \sa casus_blue_grey
             */
            constexpr auto casus_blue_gray = casus_blue_grey;

            /**
             * The color "CASUS Blue Gray 20%". This is an alias for the color "CASUS Blue Grey 20%".
             * \sa casus_blue_grey20
             */
            constexpr auto casus_blue_gray20 = casus_blue_grey20;

            /**
             * The color "CASUS Blue Gray 40%". This is an alias for the color "CASUS Blue Grey 40%".
             * \sa casus_blue_grey40
             */
            constexpr auto casus_blue_gray40 = casus_blue_grey40;

            /**
             * The color "CASUS Blue Gray 60%". This is an alias for the color "CASUS Blue Grey 60%".
             * \sa casus_blue_grey60
             */
            constexpr auto casus_blue_gray60 = casus_blue_grey60;

            /**
             * The color "CASUS Blue Gray 125%". This is an alias for the color "CASUS Blue Grey 125%".
             * \sa casus_blue_grey125
             */
            constexpr auto casus_blue_gray125 = casus_blue_grey125;

            /**
             * The color "CASUS Blue Gray 150%". This is an alias for the color "CASUS Blue Grey 150%".
             * \sa casus_blue_grey150
             */
            constexpr auto casus_blue_gray150 = casus_blue_grey150;

            /**
             * The color "CASUS Dark Blue":
             * <span style="background-color: #005096;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_dark_blue = 0xFF005096u;

            /**
             * The color "CASUS Dark Blue 20%":
             * <span style="background-color: #B7DDFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_dark_blue20 = 0xFFB7DDFFu;

            /**
             * The color "CASUS Dark Blue 40%":
             * <span style="background-color: #6FBCFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_dark_blue40 = 0xFF6FBCFFu;

            /**
             * The color "CASUS Dark Blue 60%":
             * <span style="background-color: #279AFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_dark_blue60 = 0xFF279AFFu;

            /**
             * The color "CASUS Dark Blue 125%":
             * <span style="background-color: #005096;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_dark_blue125 = 0xFF003C71u;

            /**
             * The color "CASUS Dark Blue 150%":
             * <span style="background-color: #00284B;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_dark_blue150 = 0xFF00284Bu;

            /**
             * The color "CASUS Green":
             * <span style="background-color: #A0E300;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green = 0xFFA0E300u;

            /**
             * The color "CASUS Green 60%":
             * <span style="background-color: #CDFF55;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green60 = 0xFFCDFF55u;

            /**
             * The color "CASUS Green 40%":
             * <span style="background-color: #DEFF8E;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green40 = 0xFFDEFF8Eu;

            /**
             * The color "CASUS Green 20%":
             * <span style="background-color: #EEFFC6;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green20 = 0xFFEEFFC6u;

            /**
             * The color "CASUS Green 125%":
             * <span style="background-color: #78AA00;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green125 = 0xFF78AA00u;

            /**
             * The color "CASUS Green 150%":
             * <span style="background-color: #507200;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green150 = 0xFF507200u;

            /**
             * The color "CASUS Green (Alternative)":
             * <span style="background-color: #70AD47;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green_alt = 0xFF70AD47u;

            /**
             * The color "CASUS Green (Alternative) 20%":
             * <span style="background-color: #E2F0D9;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green_alt20 = 0xFFE2F0D9u;

            /**
             * The color "CASUS Green (Alternative) 40%":
             * <span style="background-color: #C5E0B4;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green_alt40 = 0xFFC5E0B4u;

            /**
             * The color "CASUS Green (Alternative) 60%":
             * <span style="background-color: #A9D18E;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green_alt60 = 0xFFA9D18Eu;

            /**
             * The color "CASUS Green (Alternative) 125%":
             * <span style="background-color: #548235;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green_alt125 = 0xFF548235u;

            /**
             * The color "CASUS Green (Alternative) 150%":
             * <span style="background-color: #385723;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_green_alt150 = 0xFF385723u;

            /**
             * The color "CASUS Grey":
             * <span style="background-color: #A1A1A1;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_grey = 0xFFA1A1A1u;

            /**
             * The color "CASUS Grey" 20%:
             * <span style="background-color: #ECECEC;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_grey20 = 0xFFECECECu;

            /**
             * The color "CASUS Grey" 40%:
             * <span style="background-color: #D9D9D9;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_grey40 = 0xFFD9D9D9u;

            /**
             * The color "CASUS Grey" 60%:
             * <span style="background-color: #C7C7C7;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_grey60 = 0xFFC7C7C7u;

            /**
             * The color "CASUS Grey" 125%:
             * <span style="background-color: #797979;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_grey125 = 0xFF797979u;

            /**
             * The color "CASUS Grey" 150%:
             * <span style="background-color: #515151;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_grey150 = 0xFF515151u;

            /**
             * The color "CASUS Gray". This is an alias for the color "CASUS Grey".
             * \sa casus_grey
             */
            constexpr auto casus_gray = casus_grey;

            /**
             * The color "CASUS Gray" 20%. This is an alias for the color "CASUS Grey" 20%.
             * \sa casus_grey20
             */
            constexpr auto casus_gray20 = casus_grey20;

            /**
             * The color "CASUS Gray" 40%. This is an alias for the color "CASUS Grey" 40%.
             * \sa casus_grey40
             */
            constexpr auto casus_gray40 = casus_grey40;

            /**
             * The color "CASUS Gray" 60%. This is an alias for the color "CASUS Grey" 60%.
             * \sa casus_grey60
             */
            constexpr auto casus_gray60 = casus_grey60;

            /**
             * The color "CASUS Gray" 125%. This is an alias for the color "CASUS Grey" 125%.
             * \sa casus_grey125
             */
            constexpr auto casus_gray125 = casus_grey125;

            /**
             * The color "CASUS Gray" 150%. This is an alias for the color "CASUS Grey" 150%.
             * \sa casus_grey150
             */
            constexpr auto casus_gray150 = casus_grey150;

            /**
             * The color "CASUS Light Grey":
             * <span style="background-color: #E7E6E6;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_light_grey = 0xFFE7E6E6u;

            /**
             * The color "CASUS Light Grey" 110%:
             * <span style="background-color: #D0CECE;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_light_grey110 = 0xFFD0CECEu;

            /**
             * The color "CASUS Light Grey" 125%:
             * <span style="background-color: #AFABAB;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_light_grey125 = 0xFFAFABABu;

            /**
             * The color "CASUS Light Grey" 150%:
             * <span style="background-color: #767171;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_light_grey150 = 0xFF767171u;

            /**
             * The color "CASUS Light Grey" 175%:
             * <span style="background-color: #3B3838;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_light_grey175 = 0xFF3B3838u;

            /**
             * The color "CASUS Light Grey" 190%:
             * <span style="background-color: #181717;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_light_grey190 = 0xFF181717u;

            /**
             * The color "CASUS Light Gray". This is an alias for the color "CASUS Light Grey".
             * \sa casus_light_grey
             */
            constexpr auto casus_light_gray = casus_light_grey;

            /**
             * The color "CASUS Light Gray" 110%. This is an alias for the color "CASUS Light Grey" 110%.
             * \sa casus_light_grey110
             */
            constexpr auto casus_light_gray110 = casus_light_grey110;

            /**
             * The color "CASUS Light Gray" 125%. This is an alias for the color "CASUS Light Grey" 125%.
             * \sa casus_light_grey125
             */
            constexpr auto casus_light_gray125 = casus_light_grey125;

            /**
             * The color "CASUS Light Gray" 150%. This is an alias for the color "CASUS Light Grey" 150%.
             * \sa casus_light_grey150
             */
            constexpr auto casus_light_gray150 = casus_light_grey150;

            /**
             * The color "CASUS Light Gray" 175%. This is an alias for the color "CASUS Light Grey" 175%.
             * \sa casus_light_grey175
             */
            constexpr auto casus_light_gray175 = casus_light_grey175;

            /**
             * The color "CASUS Light Gray" 190%. This is an alias for the color "CASUS Light Grey" 190%.
             * \sa casus_light_grey190
             */
            constexpr auto casus_light_gray190 = casus_light_grey190;

            /**
             * The color "CASUS Turquoise":
             * <span style="background-color: #00C3FF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_turquoise = 0xFF00C3FFu;

            /**
             * The color "CASUS Turquoise" 20%:
             * <span style="background-color: #CCF3FF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_turquoise20 = 0xFFCCF3FFu;

            /**
             * The color "CASUS Turquoise" 40%:
             * <span style="background-color: #99E7FF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_turquoise40 = 0xFF99E7FFu;

            /**
             * The color "CASUS Turquoise" 60%:
             * <span style="background-color: #66DBFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_turquoise60 = 0xFF66DBFFu;

            /**
             * The color "CASUS Turquoise" 125%:
             * <span style="background-color: #0092BF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_turquoise125 = 0xFF0092BFu;

            /**
             * The color "CASUS Turquoise" 150%:
             * <span style="background-color: #00617F;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_turquoise150 = 0xFF00617Fu;

            /**
             * The color "CASUS White":
             * <span style="background-color: #FFFFFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_white = 0xFFFFFFFFu;

            /**
             * The color "CASUS White" 105%:
             * <span style="background-color: #F2F2F2;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_white105 = 0xFFF2F2F2u;

            /**
             * The color "CASUS White" 115%:
             * <span style="background-color: #D9D9D9;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_white115 = 0xFFD9D9D9u;

            /**
             * The color "CASUS White" 125%:
             * <span style="background-color: #BFBFBF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_white125 = 0xFFBFBFBFu;

            /**
             * The color "CASUS White" 135%:
             * <span style="background-color: #A6A6A6;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_white135 = 0xFFA6A6A6u;

            /**
             * The color "CASUS White" 150%:
             * <span style="background-color: #7F7F7F;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto casus_white150 = 0xFF7F7F7Fu;

            /**
             * \}
             */ // Doxygen group "casus"

            /**
             * \defgroup bactria_colors bactria's default colors
             *
             * bactria defines some colors intended for internal usage as default parameters. These are currently
             * corresponding to some colors from the Helmholtz corporate design.
             *
             * \sa helmholtz
             * \{
             */

            /**
             * The color "bactria Blue". This is currently an alias for the color "Helmholtz Blue".
             * \sa helmholtz_blue
             */
            constexpr auto bactria_blue = helmholtz_blue;

            /**
             * The color "bactria Cyan". This is currently an alias for the color "Helmholtz Dark Cyan".
             * \sa helmholtz_dark_cyan
             */
            constexpr auto bactria_cyan = helmholtz_dark_cyan;

            /**
             * The color "bactria Dark Blue". This is currently an alias for the color "Helmholtz Dark Blue".
             * \sa helmholtz_dark_blue
             */
            constexpr auto bactria_dark_blue = helmholtz_dark_blue;

            /**
             * The color "bactria Green". This is currently an alias for the color "Helmholtz Green".
             * \sa helmholtz_green
             */
            constexpr auto bactria_green = helmholtz_green;

            /**
             * The color "bactria Grey". This is currently an alias for the color "Helmholtz Grey".
             * \sa helmholtz_grey
             */
            constexpr auto bactria_grey = helmholtz_grey;

            /**
             * The color "bactria Gray". This is an alias for the color "bactria Grey".
             * \sa bactria_grey
             */
            constexpr auto bactria_gray = helmholtz_grey;

            /**
             * The color "bactria Orange". This is currently an alias for the color "Helmholtz Orange".
             * \sa helmholtz_orange
             */
            constexpr auto bactria_orange = helmholtz_orange;

            /**
             * The color "bactria Red". This is currently an alias for the color "Helmholtz Red".
             * \sa helmholtz_red
             */
            constexpr auto bactria_red = helmholtz_red;

            /**
             * The color "bactria Ruby". This is currently an alias for the color "Helmholtz Ruby".
             * \sa helmholtz_ruby
             */
            constexpr auto bactria_ruby = helmholtz_ruby;

            /**
             * The color "bactria Turquoise". This is currently an alias for the color "Helmholtz Turquoise".
             * \sa helmholtz_turquoise
             */
            constexpr auto bactria_turquoise = helmholtz_turquoise;

            /**
             * The color "bactria Yellow". This is currently an alias for the color "Helmholtz Yellow".
             * \sa helmholtz_yellow
             */
            constexpr auto bactria_yellow = helmholtz_yellow;

            /**
             * \}
             */ // Doxygen group "bactria_colors"

            /**
             * \defgroup html HTML standard colors
             *
             * Standard HTML colors supported by most modern browsers.
             *
             * \{
             */

            /**
             * The HTML color "Black":
             * <span style="background-color: #000000;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto black = 0xFF000000u;

            /**
             * The HTML color "Blue":
             * <span style="background-color: #0000FF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto blue = 0xFF0000FFu;

            /**
             * The HTML color "Brown":
             * <span style="background-color: #A52A2A;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto brown = 0xFFA52A2Au;

            /**
             * The HTML color "Crimson":
             * <span style="background-color: #DC143C;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto crimson = 0xFFDC143Cu;

            /**
             * The HTML color "Cyan":
             * <span style="background-color: #00FFFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto cyan = 0xFF00FFFFu;

            /**
             * The HTML color "Dark Blue":
             * <span style="background-color: #00008B;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_blue = 0xFF00008Bu;

            /**
             * The HTML color "Dark Cyan":
             * <span style="background-color: #008B8B;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_cyan = 0xFF008B8Bu;

            /**
             * The HTML color "Dark Gray":
             * <span style="background-color: #A9A9A9;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_gray = 0xFFA9A9A9u;

            /**
             * The HTML color "Dark Grey":
             * <span style="background-color: #A9A9A9;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_grey = 0xFFA9A9A9u;

            /**
             * The HTML color "Dark Green":
             * <span style="background-color: #006400;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_green = 0xFF006400u;

            /**
             * The HTML color "Dark Magenta":
             * <span style="background-color: #8B008B;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_magenta = 0xFF8B008Bu;

            /**
             * The HTML color "Dark Orange":
             * <span style="background-color: #FF8C00;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_orange = 0xFFFF8C00u;

            /**
             * The HTML color "Dark Red":
             * <span style="background-color: #8B0000;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_red = 0xFF8B0000u;

            /**
             * The HTML color "Dark Violet":
             * <span style="background-color: #9400D3;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_violet = 0xFF9400D3u;

            /**
             * The HTML color "Dark Turquoise":
             * <span style="background-color: #00CED1;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto dark_turquoise = 0xFF00CED1u;

            /**
             * The HTML color "Gold":
             * <span style="background-color: #FFD700;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto gold = 0xFFFFD700u;

            /**
             * The HTML color "Gray":
             * <span style="background-color: #808080;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto gray = 0xFF808080u;

            /**
             * The HTML color "Green":
             * <span style="background-color: #008000;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto green = 0xFF008000u;

            /**
             * The HTML color "Grey":
             * <span style="background-color: #808080;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto grey = 0xFF808080u;

            /**
             * The HTML color "Light Blue":
             * <span style="background-color: #ADD8E6;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto light_blue = 0xFFADD8E6u;

            /**
             * The HTML color "Light Cyan":
             * <span style="background-color: #E0FFFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto light_cyan = 0xFFE0FFFFu;

            /**
             * The HTML color "Light Gray":
             * <span style="background-color: #D3D3D3;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto light_gray = 0xFFD3D3D3u;

            /**
             * The HTML color "Light Grey":
             * <span style="background-color: #D3D3D3;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto light_grey = 0xFFD3D3D3u;

            /**
             * The HTML color "Light Green":
             * <span style="background-color: #90EE90;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto light_green = 0xFF90EE90u;

            /**
             * The HTML color "Light Yellow":
             * <span style="background-color: #FFFFE0;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto light_yellow = 0xFFFFFFE0u;

            /**
             * The HTML color "Lime":
             * <span style="background-color: #00FF00;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto lime = 0xFF00FF00u;

            /**
             * The HTML color "Magenta":
             * <span style="background-color: #FF00FF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto magenta = 0xFFFF00FFu;

            /**
             * The HTML color "Maroon":
             * <span style="background-color: #800000;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto maroon = 0xFF800000u;

            /**
             * The HTML color "Medium Blue":
             * <span style="background-color: #0000CD;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto medium_blue = 0xFF0000CDu;

            /**
             * The HTML color "Medium Purple":
             * <span style="background-color: #9370DB;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto medium_purple = 0xFF9370DBu;

            /**
             * The HTML color "Medium Turquoise":
             * <span style="background-color: #48D1CC;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto medium_turquoise = 0xFF48D1CCu;

            /**
             * The HTML color "Olive":
             * <span style="background-color: #808000;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto olive = 0xFF808000u;

            /**
             * The HTML color "Orange":
             * <span style="background-color: #FFA500;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto orange = 0xFFFFA500u;

            /**
             * The HTML color "Pink":
             * <span style="background-color: #FFC0CB;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto pink = 0xFFFFC0CBu;

            /**
             * The HTML color "Purple":
             * <span style="background-color: #800080;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto purple = 0xFF800080u;

            /**
             * The HTML color "Red":
             * <span style="background-color: #FF0000;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto red = 0xFFFF0000u;

            /**
             * The HTML color "Silver":
             * <span style="background-color: #C0C0C0;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto silver = 0xFFC0C0C0u;

            /**
             * The HTML color "Turquoise":
             * <span style="background-color: #40E0D0;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto turquoise = 0xFF40E0D0u;

            /**
             * The HTML color "Violet":
             * <span style="background-color: #EE82EE;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto violet = 0xFFEE82EEu;

            /**
             * The HTML color "Yellow":
             * <span style="background-color: #FFFF00;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto yellow = 0xFFFFFF00u;

            /**
             * The HTML color "White":
             * <span style="background-color: #FFFFFF;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
             */
            constexpr auto white = 0xFFFFFFFFu;

            /**
             * \}
             */ // Doxygen group "html"

            /**
             * \}
             */ // Doxygen group "colors"
        } // namespace color
    } // namespace ranges
} // namespace bactria
