#ifndef PLAYERBACKEND_H
#define PLAYERBACKEND_H

/***************************************************************************
 *   Copyright (C) 2007-2009 Sergio Pistone (sergio_pistone@yahoo.com.ar)  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include "servicebackend.h"
#include "player.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QWidget>

namespace SubtitleComposer
{
	class PlayerBackend : public ServiceBackend
	{
		Q_OBJECT

		friend class Player;

		public:

			// FIXME there should be a way for backends to abort on error

			/// ownership of the config object is transferred to this object
			PlayerBackend( Player* player, const QString& name, AppConfigGroup* config );
			virtual ~PlayerBackend();

		protected:

			virtual bool doesVolumeCorrection() const;
			virtual bool supportsChangingAudioStream( bool* onTheFly ) const;

			/**
			Return false if there is an error and the opening of the file must be aborted,
			otherwise, return true (all internal cleanup must be done before returning).
			If the player is not leaved in a state where is about to start playing after
			the call, it must set the content of playingAfterCall to false; otherwise it's
			content must be set to true.
			The function doesn't need to block until playback is actually started
			*/
			virtual bool openFile( const QString& filePath, bool& playingAfterCall ) = 0;

			/**
			Cleanup any internal structures associated with the opened file. This function
			is called with the player already stopped.
			videoWidget() might be NULL when this function is called.
			*/
			virtual void closeFile() = 0;

			/**
			Return false if there is an error and playback must be aborted;	otherwise return
			true (all internal cleanup must be done before returning).
			*/
			virtual bool play() = 0;

			/**
			Return false if there is an error and playback must be aborted;	otherwise return
			true (all internal cleanup must be done before returning).
			*/
			virtual bool pause() = 0;

			/**
			Return false if there is an error and playback must be aborted;	otherwise return
			true (all internal cleanup must be done before returning).
			*/
			virtual bool seek( double seconds, bool accurate ) = 0;

			/**
			Return false if there is an error and playback must be aborted;	otherwise return
			true (all internal cleanup must be done before returning).
			*/
			virtual bool stop() = 0;

			/**
			Return false if there is an error and playback must be aborted;	otherwise return
			true (all internal cleanup must be done before returning).
			*/
			virtual bool setActiveAudioStream( int audioStream ) = 0;

			/**
			Return false if there is an error and playback must be aborted;	otherwise return
			true (all internal cleanup must be done before returning).
			*/
			virtual bool setVolume( double volume ) = 0;

			inline Player* player() const { return static_cast<Player*>( service() ); }
	};
}

#endif
