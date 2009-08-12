<?php
// $Id: color.inc,v 1.1.2.1 2009/05/04 07:32:29 zinv Exp $

$info = array(

  // Pre-defined color schemes.
  'schemes' => array(
    '#e1eff5,#f23183,#000000,#000000,#5e6568' => t('Magazeen (Default)'),
    '#e8eaeb,#2f416f,#2a2b2d,#5d6779,#494949' => t('Ash'),
    '#d0f3ff,#000000,#085360,#007e94,#696969' => t('Aquamarine'),
    '#ffebb5,#6c420e,#331900,#971702,#494949' => t('Belgian Chocolate'),
    '#eaeae9,#336699,#6598cb,#6598cb,#000000' => t('Bluemarine'),
    '#f3eee0,#917803,#efde01,#e6fb2d,#494949' => t('Citrus Blast'),
    '#e8e0f3,#434f8c,#4d91ff,#1a1575,#000000' => t('Cold Day'),
    '#f3f3e0,#0c7a00,#03961e,#7be000,#494949' => t('Greenbeam'),
    '#f7eebb,#a9290a,#fc6d1d,#a30f42,#494949' => t('Mediterrano'),
    '#dfecfe,#3f728d,#a9adbc,#d4d4d4,#707070' => t('Mercury'),
    '#e1e0f3,#5b5faa,#0a2352,#9fa8d5,#494949' => t('Nocturnal'),
    '#ddffa1,#6a9915,#b5d52a,#7db323,#191a19' => t('Olivia'),
    '#f4e4ed,#1b1a13,#f391c6,#f41063,#898080' => t('Pink Plastic'),
    '#f7e0fa,#c70000,#a1443a,#f21107,#515d52' => t('Shiny Tomato'),
    '#c3ffe6,#1b5f42,#34775a,#52bf90,#2d2d2d' => t('Teal Top'),
  ),

  // Images to copy over.
  'copy' => array(
    'logo.png',
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'css/general.css',
    'css/typography.css',
    'css/style.css',
  ),

  // Coordinates of gradient (x, y, width, height).
  'gradient' => array(0, 0, 1020, 218),

  // Color areas to fill (x, y, width, height).
  'fill' => array(
    'base' => array(0, 0, 1020, 1240),
  ),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(
    'images/header.png'                      => array(16, 0, 1, 177),
    'images/navigation-hover.png'            => array(100, 173, 1, 45),
    'images/dock.png'                        => array(971, 260, 1, 126),
    'images/dock-back.png'                   => array(40, 260, 940, 170),
    'images/main-content.png'                => array(40, 432, 940, 111),
    'images/post-box-top.png'                => array(50, 584, 1, 22),
    'images/sidebar-top.png'                 => array(658, 584, 305, 83),
    'images/sidebar-middle.png'              => array(658, 667, 305, 1),
    'images/sidebar-bottom.png'              => array(658, 1082, 305, 73),
    'images/submit-comment.png'              => array(69, 1031, 127, 60),
    'images/gradient-inner.png'              => array(40, 1195, 112, 42),
  ),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  'preview_image' => 'color/preview.png',
  'preview_css' => 'color/preview.css',

  // Base file for image generation.
  'base_image' => 'color/base.png',
);