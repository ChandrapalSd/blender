/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2006 Blender Foundation.
 * All rights reserved.
 */

/** \file
 * \ingroup cmpnodes
 */

#include "UI_interface.h"
#include "UI_resources.h"

#include "../node_composite_util.hh"

/* **************** Bokeh image Tools  ******************** */

namespace blender::nodes {

static void cmp_node_bokehimage_declare(NodeDeclarationBuilder &b)
{
  b.add_output<decl::Color>(N_("Image"));
}

}  // namespace blender::nodes

static void node_composit_init_bokehimage(bNodeTree *UNUSED(ntree), bNode *node)
{
  NodeBokehImage *data = (NodeBokehImage *)MEM_callocN(sizeof(NodeBokehImage), "NodeBokehImage");
  data->angle = 0.0f;
  data->flaps = 5;
  data->rounding = 0.0f;
  data->catadioptric = 0.0f;
  data->lensshift = 0.0f;
  node->storage = data;
}

static void node_composit_buts_bokehimage(uiLayout *layout, bContext *UNUSED(C), PointerRNA *ptr)
{
  uiItemR(layout, ptr, "flaps", UI_ITEM_R_SPLIT_EMPTY_NAME, nullptr, ICON_NONE);
  uiItemR(layout, ptr, "angle", UI_ITEM_R_SPLIT_EMPTY_NAME, nullptr, ICON_NONE);
  uiItemR(
      layout, ptr, "rounding", UI_ITEM_R_SPLIT_EMPTY_NAME | UI_ITEM_R_SLIDER, nullptr, ICON_NONE);
  uiItemR(layout,
          ptr,
          "catadioptric",
          UI_ITEM_R_SPLIT_EMPTY_NAME | UI_ITEM_R_SLIDER,
          nullptr,
          ICON_NONE);
  uiItemR(layout, ptr, "shift", UI_ITEM_R_SPLIT_EMPTY_NAME | UI_ITEM_R_SLIDER, nullptr, ICON_NONE);
}

void register_node_type_cmp_bokehimage()
{
  static bNodeType ntype;

  cmp_node_type_base(&ntype, CMP_NODE_BOKEHIMAGE, "Bokeh Image", NODE_CLASS_INPUT, NODE_PREVIEW);
  ntype.declare = blender::nodes::cmp_node_bokehimage_declare;
  ntype.draw_buttons = node_composit_buts_bokehimage;
  node_type_init(&ntype, node_composit_init_bokehimage);
  node_type_storage(
      &ntype, "NodeBokehImage", node_free_standard_storage, node_copy_standard_storage);

  nodeRegisterType(&ntype);
}
