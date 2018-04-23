//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// speechapi_cxx_speech_recognizer.h: Public API declarations for SpeechRecognizer C++ class
//

#pragma once
#include <exception>
#include <future>
#include <memory>
#include <string>
#include <speechapi_cxx_common.h>
#include <speechapi_c.h>
#include <speechapi_cxx_recognition_async_recognizer.h>
#include <speechapi_cxx_speech_recognition_eventargs.h>
#include <speechapi_cxx_speech_recognition_result.h>
#include <speechapi_cxx_recognizer_parameter_collection.h>


namespace Microsoft {
namespace CognitiveServices {
namespace Speech {

class Session;


namespace Recognition {
namespace Speech {


class SpeechRecognizer final : virtual public AsyncRecognizer<SpeechRecognitionResult, SpeechRecognitionEventArgs>
{
public:

    using BaseType = AsyncRecognizer<SpeechRecognitionResult, SpeechRecognitionEventArgs>;

    /// <summary>
    /// Internal constructor. Creates a new instance using the provided handle.
    /// </summary>
    SpeechRecognizer(SPXRECOHANDLE hreco) : BaseType(hreco), Parameters(hreco)
    {
        SPX_DBG_TRACE_FUNCTION();
    }

    /// <summary>
    /// Destructor.
    /// </summary>
    ~SpeechRecognizer()
    {
        SPX_DBG_TRACE_FUNCTION();
    }

    /// <summary>
    /// Performs speech recognition in a non-blocking (asynchronous) mode.
    /// </summary>
    /// <returns>Future containing result value (a shared pointer to IntentRecognitionResult)
    /// of the asynchronous speech recognition.
    /// </returns>
    std::future<std::shared_ptr<SpeechRecognitionResult>> RecognizeAsync() override
    {
        return BaseType::RecognizeAsyncInternal();
    }

    /// <summary>
    /// Asynchronously initiates continuous speech recognition operation.
    /// </summary>
    /// <returns>An empty future.</returns>
    std::future<void> StartContinuousRecognitionAsync() override
    {
        return BaseType::StartContinuousRecognitionAsyncInternal();
    }

    /// <summary>
    /// Asynchronously terminates ongoing continuous speech recognition operation.
    /// </summary>
    /// <returns>An empty future.</returns>
    std::future<void> StopContinuousRecognitionAsync() override
    {
        return BaseType::StopContinuousRecognitionAsyncInternal();
    }

    /// <summary>
    /// Asynchronously initiates keyword recognition operation.
    /// </summary>
    /// <returns>An empty future.</returns>
    std::future<void> StartKeywordRecognitionAsync(const std::wstring& keyword) override
    {
        return BaseType::StartKeywordRecognitionAsyncInternal(keyword);
    }

    /// <summary>
    /// Asynchronously terminates keyword recognition operation.
    /// </summary>
    /// <returns>An empty future.</returns>
    std::future<void> StopKeywordRecognitionAsync() override
    {
        return BaseType::StopKeywordRecognitionAsyncInternal();
    }

    RecognizerParameterValueCollection Parameters;

    /// <summary>
    /// Sets the deployment id if the recognizer uses a customized model for recognition.
    /// </summary>
    /// <param name="value">A string that represents the deployment id.</param>
    void SetDeploymentId(const std::wstring& deploymentId)
    {
        Parameters[RecognizerParameter::DeploymentId] = deploymentId;
    }


private:

    SpeechRecognizer() = delete;
    SpeechRecognizer(SpeechRecognizer&&) = delete;
    SpeechRecognizer(const SpeechRecognizer&) = delete;
    SpeechRecognizer& operator=(SpeechRecognizer&&) = delete;
    SpeechRecognizer& operator=(const SpeechRecognizer&) = delete;

    friend class Microsoft::CognitiveServices::Speech::Session;
};


} } } } } // Microsoft::CognitiveServices::Speech::Recognition::Speech
