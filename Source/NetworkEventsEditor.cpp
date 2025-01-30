/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2024 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "NetworkEventsEditor.h"
#include "NetworkEvents.h"

#include <stdio.h>

NetworkEventsEditor::NetworkEventsEditor (NetworkEvents* parentNode) : GenericEditor (parentNode)

{
    desiredWidth = 180;

    processor = parentNode;

    restartConnection = std::make_unique<UtilityButton> ("Restart");
    restartConnection->setBounds (20, 45, 130, 22);
    restartConnection->addListener (this);
    addAndMakeVisible (restartConnection.get());

    addTextBoxParameterEditor (Parameter::ParameterScope::PROCESSOR_SCOPE, "port", 20, 80);
    addToggleParameterEditor (Parameter::ParameterScope::PROCESSOR_SCOPE, "broadcast_all_messages", 20, 100);
}

NetworkEventsEditor::~NetworkEventsEditor() = default;

void NetworkEventsEditor::buttonClicked (Button* button)
{
    processor->restartConnection();
}