<?php

/**
 * XML callback.
 */
function imagefield_dewslider_xml($node, $format, $field_name) {
  $options=imagefield_dewslider_get_options($field_name, $format=='teaser');

  drupal_set_header('Content-Type: text/xml; charset: utf-8');
  
  $params = array(
    'showbuttons',
    'showtitles',
    'randomstart',
    'timer',
    'aligntitles',
    'alignbuttons',
    'transition',
    'speed',
  );
  
  $data = '<?xml version="1.0" ?><album';
  foreach ($params as $param) {
    if ($options[$param]) $data .= ' ' . $param . '="' . $options[$param] . '"';
  }
  $data .= '>';
  
  if (isset($node->$field_name) && is_array($node->$field_name)) {
    foreach ($node->$field_name as $delta => $value)
    {
      $src = imagecache_create_url($options['imagecache'], $value['filepath']);
      $title = $value['data']['title'];
      if ($options['trimtitles']>0&&drupal_strlen($title)>$options['trimtitles']) {
        $title = drupal_substr($title, 0, $options['trimtitles']) . '...';
      }
      $data .= '<img src="' . htmlspecialchars($src) . '" title="' . htmlspecialchars($title) . '"/>';
    }
  }
  
  $data .= '</album>';
  
  die($data);
}