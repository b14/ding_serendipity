<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

$plugin = array(
  'title' => t('Ding serendipity content'),
  'description' => t('Display serendipity content'),
  'admin info' => 'ding_serendipity_admin_info',
  'single' => TRUE,
  'defaults' => array('ding_serendipity_count' => 3, 'ding_serendipity_offset' => 0),
  'required context' => array(
      new ctools_context_optional(t('Page node'), 'node'),
      new ctools_context_optional(t('Search term'), 'string'),
      new ctools_context_optional(t('Taxonomy terms'), 'terms')),
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration information in panels.
 */
function ding_serendipity_admin_info($subtype, $conf, $context) {
  $output = new stdClass();
  $output->title = t('Serendipity');
  $output->content = t('Serendipity content. Count: @count, Offset: @offset', array('@count' => $conf['ding_serendipity_count'], '@offset' => $conf['ding_serendipity_offset']));
  return $output;
}

/**
 * Implements hook_content_type_render().
 */
function ding_serendipity_serendipity_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $context_data = array(
    'page' => isset($context[0]->data) ? $context[0]->data : NULL,
    'search_term' => isset($context[1]->data) ? $context[1]->data : NULL,
    'taxonomy_term' => isset($context[2]->data) ? $context[2]->data : NULL,
  );
  
  $count = $conf['ding_serendipity_count'];
  $offset = $conf['ding_serendipity_offset'];
  
  /*
  $results = ding_serendipity_fetch($context_data);
  $items = array_slice($results['items'], $offset, $count);
  
  $content = array();
  foreach ($items as $result) {
    $ting = ting_collection_load($result['id']);
    $content[] = ting_collection_view($ting, 'teaser');
  }
  */
  
  $block->content = ding_serendipity_render($context_data);
  

  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_serendipity_content_type_edit_form($form, &$form_state) {

  $form['ding_serendipity_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity count'),
    '#description' => t('The maximum number of items to display'),
    '#default_value' => (isset($form_state['conf']['ding_serendipity_count'])) ? $form_state['conf']['ding_serendipity_count'] : DING_CAMPAIGN_DEFAULT_COUNT,
    '#size' => 2,
    '#maxlength' => 2,
  );

  $form['ding_serendipity_offset'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity offset'),
    '#description' => t('Which serendipity content should we count from when returning campaigns. This is used to avoid displaying the same items when using multiple serendipity panes on the same panel. Use 0 to return the most relevant serendipity content.'),
    '#default_value' => (isset($form_state['conf']['ding_serendipity_offset'])) ? $form_state['conf']['ding_serendipity_offset'] : 0,
    '#size' => 3,
    '#maxlength' => 3,
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_serendipity_serendipity_content_type_edit_form_validate($form, &$form_state) {
  // Sanitise the submitted values.
  $values = array('ding_serendipity_count' => 1, 'ding_serendipity_offset' => 0);
  foreach ($values as $value => $min_value) {
    $val = trim($form_state['values'][$value]);
    $count = intval($val);

    // Give an error if a value less than 1 was entered.
    if (!empty($val) && $count < $min_value) {
      form_set_error($value, t('%value must be a number larger than zero.', array('%value' => ucfirst(str_replace('_', ' ', $value)))));
    }
    // Otherwise, store the sanitised value in the form state.
    else {
      $form_state['values'][$value] = $count;
    }
  }
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_serendipity_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['ding_serendipity_count'] = $form_state['values']['ding_serendipity_count'];
  $form_state['conf']['ding_serendipity_offset'] = $form_state['values']['ding_serendipity_offset'];
}

/**
 * Setup a base form for serendipity ctools content types.
 */
function ding_serendipity_form_base($form_state) {
  $form['view_mode'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => array(
      'full' => t('Full'),
      'teaser' => t('Teaser'),
      'big_teaser' => t('Big teaser'),
      'grid_item' => t('Grid item'),
      'list_item_short' => t('Short list item'),
    ),
    '#default_value' => (isset($form_state['conf']['view_mode'])) ? $form_state['conf']['view_mode'] : 'full',
    '#description' => t('Select the view mode which the content will display with.'),
  );
  $form['sort_weight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort by by weight.'),
    '#default_value' => (isset($form_state['conf']['random'])) ? $form_state['conf']['sort_weight'] : 0,
  );
  $form['max'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity maximum'),
    '#description' => t('The maximum number of items to display.'),
    '#default_value' => (isset($form_state['conf']['max'])) ? $form_state['conf']['max'] : 2,
    '#size' => 2,
    '#maxlength' => 2,
  );
  $form['min'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity minimum'),
    '#description' => t('Select the minimum amount of items displayed.'),
    '#default_value' => (isset($form_state['conf']['min'])) ? $form_state['conf']['min'] : 0,
    '#size' => 3,
    '#maxlength' => 3,
  );
  $form['random'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort by random order.'),
    '#default_value' => (isset($form_state['conf']['random'])) ? $form_state['conf']['random'] : 0,
  );
  return $form;
}

function ding_serendipity_form_base_validate($form, &$form_state) {
  // Validation stuff
}

function ding_serendipity_form_base_submit(&$form_state) {
  $form_state['conf']['view_mode'] = !empty($form_state['values']['view_mode']) ? $form_state['values']['view_mode'] : 'big_teaser';
  $form_state['conf']['sort_weight'] = !empty($form_state['values']['sort_weight']) ? $form_state['values']['sort_weight'] : FALSE;
  $form_state['conf']['max'] = !empty($form_state['values']['max']) ? $form_state['values']['max'] : 3;
  $form_state['conf']['min'] = !empty($form_state['values']['min']) ? $form_state['values']['min'] : 3;
  $form_state['conf']['random'] = !empty($form_state['values']['random']) ? $form_state['values']['random'] : FALSE;
}
