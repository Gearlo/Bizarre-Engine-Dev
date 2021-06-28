/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MCore Additional
// MWavSoundLoader.cpp
//
// simple wav Sound loader
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#include <stdio.h>
#include <BCore.h>
#include <BLoaders.h>

#include <libopenmpt/libopenmpt.h>
#include <libopenmpt/libopenmpt_stream_callbacks_file.h>

#define MODSAMPLERATE 44100
#define MODBUFFER 44100

static int16_t modBuffer[MODBUFFER];

static void libopenmpt_example_logfunc( const char * message, void * userdata ) {
	(void)userdata;
	if ( message ) {
		fprintf( stderr, "openmpt: %s\n", message );
	}
}

static int libopenmpt_example_errfunc( int error, void * userdata ) {
	(void)userdata;
	(void)error;
	return OPENMPT_ERROR_FUNC_RESULT_DEFAULT & ~OPENMPT_ERROR_FUNC_RESULT_LOG;
}

static void libopenmpt_example_print_error( const char * func_name, int mod_err, const char * mod_err_str ) {
	if ( !func_name ) {
		func_name = "unknown function";
	}
	if ( mod_err == OPENMPT_ERROR_OUT_OF_MEMORY ) {
		mod_err_str = openmpt_error_string( mod_err );
		if ( !mod_err_str ) {
			fprintf( stderr, "Error: %s\n", "OPENMPT_ERROR_OUT_OF_MEMORY" );
		} else {
			fprintf( stderr, "Error: %s\n", mod_err_str );
			openmpt_free_string( mod_err_str );
			mod_err_str = NULL;
		}
	} else {
		if ( !mod_err_str ) {
			mod_err_str = openmpt_error_string( mod_err );
			if ( !mod_err_str ) {
				fprintf( stderr, "Error: %s failed.\n", func_name );
			} else {
				fprintf( stderr, "Error: %s failed: %s\n", func_name, mod_err_str );
			}
			openmpt_free_string( mod_err_str );
			mod_err_str = NULL;
		}
		fprintf( stderr, "Error: %s failed: %s\n", func_name, mod_err_str );
	}
}


bool B_loadModMusic(const char * filename, void * data)
{
	BFile * file = M_fopen(filename, "rb");
	if(! file)
	{
		printf("ERROR Load Sound : unable to read %s file\n", filename);
		return false;
	}
	
	file->seek( 0L, SEEK_END );
	long size = file->tell();
	file->rewind();

	void* modData = new char[size];
	M_fread( modData, sizeof(char), size, file );
	M_fclose(file);
	

	openmpt_module * mod = 0;
	int mod_err = OPENMPT_ERROR_OK;
	const char * mod_err_str = NULL;
	double mod_duration;

	mod = openmpt_module_create_from_memory2( modData, size, &libopenmpt_example_logfunc, NULL, &libopenmpt_example_errfunc, NULL, &mod_err, &mod_err_str, NULL );
	//mod = openmpt_module_create2( openmpt_stream_get_file_callbacks(), file, &libopenmpt_example_logfunc, NULL, &libopenmpt_example_errfunc, NULL, &mod_err, &mod_err_str, NULL );
	if ( !mod ) {
		libopenmpt_example_print_error( "openmpt_module_create_from_memory2()", mod_err, mod_err_str );
		openmpt_free_string( mod_err_str );
		mod_err_str = NULL;
		return false;
	}
	openmpt_module_set_error_func( mod, NULL, NULL );

	
	mod_duration = openmpt_module_get_duration_seconds( mod );
	unsigned long fullBufferSize = (unsigned long)( (mod_duration+1.0) * MODSAMPLERATE );

		
	
	int16_t * fullModBuffer = new int16_t[fullBufferSize*2];
	unsigned long k = 0;

	long count = 1;
	
	while(count){
		openmpt_module_error_clear( mod );
		count = openmpt_module_read_interleaved_stereo( mod, MODSAMPLERATE, MODBUFFER, modBuffer );
		mod_err = openmpt_module_error_get_last( mod );
		mod_err_str = openmpt_module_error_get_last_message( mod );
		if ( mod_err != OPENMPT_ERROR_OK ) {
			libopenmpt_example_print_error( "openmpt_module_read_stereo()", mod_err, mod_err_str );
			openmpt_free_string( mod_err_str );
			mod_err_str = NULL;
		}
		
		memcpy ( (void*)&fullModBuffer[k], modBuffer, count*sizeof(int16_t)*2 );
		k += count*2;
	}

	if ( mod ) {
		openmpt_module_destroy( mod );
		mod = 0;
	}
	
	BSound * sound = (BSound *)data;
	sound->create(B_SOUND_FORMAT_STEREO16, k*sizeof(int16_t), MODSAMPLERATE);

	memcpy ( sound->getData(), fullModBuffer, k*sizeof(int16_t) );
	

	delete(modData);
	delete(fullModBuffer);
	return true;
}