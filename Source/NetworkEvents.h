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

#ifndef __NETWORKEVENT_H_91811541__
#define __NETWORKEVENT_H_91811541__

#include <ProcessorHeaders.h>

#include <atomic>
#include <list>
#include <queue>
#include <zmq.h>

/**
 Sends incoming TCP/IP messages from 0MQ to the events buffer

    @see GenericProcessor
*/
class NetworkEvents : public GenericProcessor, public Thread, private AsyncUpdater
{
public:
    /** Constructor */
    NetworkEvents();

    /** Destructor -- stops the network thread */
    ~NetworkEvents() override;

    /** Creates the editor */
    AudioProcessorEditor* createEditor() override;

    /** Registers parameters */
    void registerParameters() override;

    void parameterValueChanged (Parameter*) override;

    /** Triggers TTLs on the appropriate channel */
    void process (AudioBuffer<float>& buffer) override;

    /** Updates settings */
    void updateSettings() override;

    /** Runs the messaging thread */
    void run() override;

    /** Sets the port to bind to */
    void setNewListeningPort (uint16 port, bool synchronous = true);

    /** Broadcast all incoming messages **/
    void setBroadcastAllMessages (bool);

    /** Restarts the connection */
    void restartConnection();

private:
    struct StringTTL
    {
        bool onOff;
        uint8 eventLine;
        int64 tickTimestampMsgReceived; // timestamp of received message in high-resolution ticks
    };

    struct StringWord
    {
        uint64 word;
        int64 tickTimestampMsgReceived; // timestamp of received message in high-resolution ticks
    };

    class ZMQContext
    {
    public:
        ZMQContext();
        ~ZMQContext();
        void* createSocket();

    private:
        void* context;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZMQContext);
    };

    /* RAII wrapper for REP socket */
    class Responder
    {
    public:
        /* Creates socket from given context and tries to bind to port. If port is 0, chooses an available ephemeral port. */
        Responder (uint16 port);
        ~Responder();

        /* Returns the latest errno value */
        int getErr() const;

        /* Output last error on stdout and status bar, including the passed message */
        void reportErr (const String& message) const;

        bool isValid() const;

        /* Returns the port if the socket was successfully bound to one, else 0. If not, or if the socket is invalid, returns 0. */
        uint16 getBoundPort() const;

        /* Receives message into buf (blocking call). Returns the number of bytes actually received, or -1 if there is an error. */
        int receive (void* buf);

        /* Sends a message. returns the same as zmq_send. */
        int send (StringRef response);

    private:
        SharedResourcePointer<ZMQContext> context;
        void* socket;
        bool valid;
        uint16 boundPort;
        int lastErrno;

        static const int RECV_TIMEOUT_MS;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Responder);
    };

    void handleAsyncUpdate() override; // to change port asynchronously

    String handleSpecialMessages (const String& s);

    /* Split network message into name/value pairs (name1=val1 name2=val2 etc) */
    StringPairArray parseNetworkMessage (StringRef msg);

    /* Get an endpoint url for the given port (using 0 to represent *) */
    static String getEndpoint (uint16 port);

    std::atomic<bool> makeNewSocket; // port change or restart needed (depending on requestedPort)
    std::atomic<uint16> requestedPort; // never set by the thread; 0 means any free port
    std::atomic<uint16> boundPort; // only set by the thread; 0 means no connection

    std::atomic_bool broadcastAllMessages;

    std::queue<String> networkMessagesQueue;
    CriticalSection queueLock;

    std::queue<StringTTL> TTLQueue;
    CriticalSection TTLqueueLock;

    std::queue<StringWord> TTLWordQueue;
    CriticalSection TTLWordQueueLock;

    Array<EventChannel*> ttlChannels;

    void triggerTTLEvent (StringTTL TTLmsg, juce::int64 sampleNum);
    void triggerTTLWord (StringWord WordMsg, juce::int64 sampleNum);
    uint64 lastWord = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NetworkEvents);
};

#endif // __NETWORKEVENT_H_91811541__
