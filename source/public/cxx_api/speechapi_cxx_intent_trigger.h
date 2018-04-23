//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// speechapi_cxx_intent_trigger.h: Public API declarations for IntentTrigger C++ class
//

#pragma once
#include <speechapi_cxx_common.h>
#include <speechapi_c.h>
#include <speechapi_cxx_common.h>
#include <speechapi_cxx_language_understanding_model.h>


namespace Microsoft {
namespace CognitiveServices {
namespace Speech {
namespace Recognition {
namespace Intent {

/// <summary>
/// Represents an intent trigger.
/// </summary>
class IntentTrigger
{
public:

    /// <summary>
    /// Creates an intent trigger using the specified phrase.
    /// </summary>
    /// <param name="simplePhrase">The simple phrase to create an intent trigger for.</param>
    /// <returns>A shared pointer to an intent trigger.</returns>
    static std::shared_ptr<IntentTrigger> From(const std::wstring& simplePhrase)
    {
        SPXTRIGGERHANDLE htrigger = SPXHANDLE_INVALID;
        SPX_THROW_ON_FAIL(IntentTrigger_Create_From_Phrase(simplePhrase.c_str(), &htrigger));
        return std::make_shared<IntentTrigger>(htrigger);
    }

    /// <summary>
    /// Creates an intent trigger using the specified LanguageUnderstandingModel.
    /// </summary>
    /// <param name="model">The LanguageUnderstandingModel to create an intent trigger for.</param>
    /// <returns>A shared pointer to an intent trigger.</returns>
    static std::shared_ptr<IntentTrigger> From(std::shared_ptr<LanguageUnderstandingModel> model)
    {
        SPXTRIGGERHANDLE htrigger = SPXHANDLE_INVALID;
        SPX_THROW_ON_FAIL(IntentTrigger_Create_From_LanguageUnderstandingModel((SPXLUMODELHANDLE)(*model.get()), &htrigger));
        return std::make_shared<IntentTrigger>(htrigger);
    }

    /// <summary>
    /// Creates an intent trigger using the specified LanguageUnderstandingModel and an intent name.
    /// </summary>
    /// <param name="model">The LanguageUnderstandingModel to create an intent trigger for.</param>
    /// <param name="model">The intent name to create an intent trigger for.</param>
    /// <returns>A shared pointer to an intent trigger.</returns>
    static std::shared_ptr<IntentTrigger> From(std::shared_ptr<LanguageUnderstandingModel> model, const std::wstring& intentName)
    {
        SPXTRIGGERHANDLE htrigger = SPXHANDLE_INVALID;
        SPX_THROW_ON_FAIL(IntentTrigger_Create_From_LanguageUnderstandingModel_Intent((SPXLUMODELHANDLE)(*model.get()), intentName.c_str(), &htrigger));
        return std::make_shared<IntentTrigger>(htrigger);
    }

    /// <summary>
    /// Virtual destructor
    /// </summary>
    virtual ~IntentTrigger() { IntentTrigger_Handle_Close(m_htrigger); m_htrigger = SPXHANDLE_INVALID; }

    /// <summary>
    /// Internal constructor. Creates a new instance using the provided handle.
    /// </summary>
    IntentTrigger(SPXTRIGGERHANDLE htrigger) : m_htrigger(htrigger) { };

    /// <summary>
    /// Internal. Explicit conversion operator.
    /// </summary>
    explicit operator SPXTRIGGERHANDLE() { return m_htrigger; }

private:
    DISABLE_DEFAULT_CTORS(IntentTrigger);

    SPXTRIGGERHANDLE m_htrigger;
};


} } } } } // Microsoft::CognitiveServices::Speech::Recognition::Intent
