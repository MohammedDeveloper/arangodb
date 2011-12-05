////////////////////////////////////////////////////////////////////////////////
/// @brief handler factory
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2011 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2009-2011, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_FYN_REST_HTTP_HANDLER_FACTORY_H
#define TRIAGENS_FYN_REST_HTTP_HANDLER_FACTORY_H 1

#include <Basics/Common.h>

#include <Basics/Mutex.h>

////////////////////////////////////////////////////////////////////////////////
/// @defgroup HttpServer Http-Server
////////////////////////////////////////////////////////////////////////////////

namespace triagens {
  namespace rest {
    class HttpHandler;
    class HttpRequest;
    class HttpResponse;
    class MaintenanceCallback;
    class Scheduler;

    ////////////////////////////////////////////////////////////////////////////////
    /// @ingroup HttpServer
    /// @brief handler factory
    ////////////////////////////////////////////////////////////////////////////////

    class HttpHandlerFactory {
      public:
        typedef HttpHandler GeneralHandler;
        typedef HttpRequest GeneralRequest;
        typedef HttpResponse GeneralResponse;

        typedef HttpHandler* (*create_fptr) (HttpRequest*, void*);

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief constructs a new handler factory
        ////////////////////////////////////////////////////////////////////////////////

        HttpHandlerFactory ();

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief clones a handler factory
        ////////////////////////////////////////////////////////////////////////////////

        HttpHandlerFactory (HttpHandlerFactory const&);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief copies a handler factory
        ////////////////////////////////////////////////////////////////////////////////

        HttpHandlerFactory& operator= (HttpHandlerFactory const&);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief destructs a handler factory
        ////////////////////////////////////////////////////////////////////////////////

        virtual ~HttpHandlerFactory ();

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief returns header and body size restrictions
        ////////////////////////////////////////////////////////////////////////////////

        virtual pair<size_t, size_t> sizeRestrictions ();

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief creates a new request
        ////////////////////////////////////////////////////////////////////////////////

        virtual HttpRequest* createRequest (char const* ptr, size_t length);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief creates a new handler
        ////////////////////////////////////////////////////////////////////////////////

        virtual HttpHandler* createHandler (HttpRequest*);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief destroys a handler
        ////////////////////////////////////////////////////////////////////////////////

        virtual void destroyHandler (HttpHandler*);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief adds a maintenance handler
        ///
        /// Note the maintenance callback is deleted, after it is fired.
        ////////////////////////////////////////////////////////////////////////////////

        void addMaintenanceCallback (MaintenanceCallback*);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief returns the number of active handlers
        ////////////////////////////////////////////////////////////////////////////////

        size_t numberActiveHandlers ();

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief adds a path and constructor to the factory
        ////////////////////////////////////////////////////////////////////////////////

        void addHandler (string const& path, create_fptr, void* data = 0);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief adds a prefix path and constructor to the factory
        ////////////////////////////////////////////////////////////////////////////////

        void addPrefixHandler (string const& path, create_fptr, void* data = 0);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief adds a path and constructor to the factory
        ////////////////////////////////////////////////////////////////////////////////

        void addNotFoundHandler (create_fptr);

      protected:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief number of active handlers
        ////////////////////////////////////////////////////////////////////////////////

        size_t _numberActiveHandlers;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief lock for number of active handlers
        ////////////////////////////////////////////////////////////////////////////////

        basics::Mutex _activeHandlersLock;

      private:
        map<string, create_fptr> _constructors;
        map<string, void*> _datas;
        vector<string> _prefixes;

        create_fptr _notFound;

        vector<MaintenanceCallback*> _maintenanceCallbacks;
    };
  }
}

#endif
