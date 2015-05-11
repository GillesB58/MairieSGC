<?php

/**
 * @file
 */


/**
 * Handler for Dewslider display of imagecache + imagefield CCK fields.
 *
 * @param $element
 *   The CCK field element.
 * @return
 *   HTML output.
 */
function theme_imagefield_dewslider_formatter_imagefield($element) {

  $field_name = $element['#field_name'];
  $nid = $element['#node']->nid;
  $teaser = $element['#teaser'];
  
  return theme('imagefield_dewslider_dewslider', $nid, $field_name, $teaser);
}

function theme_imagefield_dewslider_dewslider($nid, $field_name, $teaser) {
  global $base_url;
  $path = drupal_get_path('module', 'imagefield_dewslider');
  $swf = $base_url . '/' . $path . '/dewslider/dewslider.swf';
  $format = $teaser ? 'teaser' : 'full';
  $xml = url("imagefield_dewslider/$nid/$format/$field_name");
  $id = "imagefield-dewslider-$nid-$format-$field_name";
  
  $options = imagefield_dewslider_get_options($field_name, $teaser);
  
  $output = '<object id="' . $id . '" width="' . $options['width'] . '" height="' . $options['height'] . '" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000">';
  $output .= '<param value="' . $swf . '?xml=' .urlencode($xml). '" name="movie"/>';
  $output .= '<param value="transparent" name="wmode"/>';
  $output .= '<embed width="' . $options['width'] . '" height="' . $options['height'] . '" pluginspace="http://www.macromedia.com/go/getflashplayer" type="application/x-shockwave-flash" wmode="transparent" src="' . $swf . '?xml=' .urlencode($xml). '"/>';
  $output .= '</object>';
  return $output;
}