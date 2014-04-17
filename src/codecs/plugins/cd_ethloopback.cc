/* $Id: decode.c,v 1.285 2013-06-29 03:03:00 rcombs Exp $ */

/*
** Copyright (C) 2002-2013 Sourcefire, Inc.
** Copyright (C) 1998-2002 Martin Roesch <roesch@sourcefire.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License Version 2 as
** published by the Free Software Foundation.  You may not use, modify or
** distribute this program under any other version of the GNU General
** Public License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "framework/codec.h"
#include "codecs/codec_events.h"
#include "codecs/decode_module.h"

namespace
{

class EthLoopbackCodec : public Codec
{
public:
    EthLoopbackCodec() : Codec("Ethloopback"){};
    ~EthLoopbackCodec();


    virtual bool decode(const uint8_t *raw_pkt, const uint32_t len, 
        Packet *, uint16_t &p_hdr_len, int &next_prot_id);

    virtual void get_protocol_ids(std::vector<uint16_t>&);
    virtual void get_data_link_type(std::vector<int>&){};
    
};

const uint16_t ETHERNET_TYPE_LOOP = 0x9000;


} // anonymous namespace

bool EthLoopbackCodec::decode(const uint8_t *raw_pkt, const uint32_t len, 
        Packet *p, uint16_t &p_hdr_len, int &next_prot_id)
{

    DEBUG_WRAP(DebugMessage(DEBUG_DECODE, "EthLoopback is not supported.\n"););

//    loopbackstats.total_packets++;

//    if (p->greh != NULL)
//        dc.gre_loopback++;

    next_prot_id = -1;
    return true;
}


//-------------------------------------------------------------------------
// api stuff
//-------------------------------------------------------------------------


void EthLoopbackCodec::get_protocol_ids(std::vector<uint16_t>& v)
{
    v.push_back(ETHERNET_TYPE_LOOP);
}

static Codec* ctor()
{
    return new EthLoopbackCodec();
}

static void dtor(Codec *cd)
{
    delete cd;
}

static void sum()
{
//    sum_stats((PegCount*)&gdc, (PegCount*)&dc, array_size(dc_pegs));
//    memset(&dc, 0, sizeof(dc));
}

static void stats()
{
//    show_percent_stats((PegCount*)&gdc, dc_pegs, array_size(dc_pegs),
//        "decoder");
}



static const char* name = "ethloopback_codec";

static const CodecApi codec_api =
{
    { PT_CODEC, name, CDAPI_PLUGIN_V0, 0 },
    NULL, // pinit
    NULL, // pterm
    NULL, // tinit
    NULL, // tterm
    ctor, // ctor
    dtor, // dtor
    sum, // sum
    stats  // stats
};
