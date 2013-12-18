<?php

$plugin = array(
  'title' => t('SMS Validation'),
  'description' => t('SMS validation information.'),
  'category' => t('Custom'),
);

/**
 * Output function for the 'SMS Validation' content type.
 *
 * Outputs a node based on the module and delta supplied in the configuration.
 */
function sms_validation_sms_validation_pane_content_type_render($subtype, $conf, $panel_args) {
  global $user;

  $block = new stdClass();
  $block->title = t('SMS Validation');

  if ($user->uid == 0) {
    if (empty($conf['message_not_logged'])) {
      $message = t('Not logged.');
    }
    else {
      $message = token_replace($conf['message_not_logged']);
    }
    $block->content = array(
      'message' => array(
        '#markup' => $message,
        '#prefix' => '<div class="message not-logged">',
        '#suffix' => '</div>'
      )
    );
    return $block;
  }

  if (sms_validation_is_active($user->uid)) {
    if (empty($conf['message_active'])) {
      $message = t('user already active.');
    }
    else {
      $message = token_replace($conf['message_active']);
    }
    $block->content = array(
      'message' => array(
        '#markup' => $message,
        '#prefix' => '<div class="message actived">',
        '#suffix' => '</div>'
      )
    );
  }
  else {
    if (empty($conf['message_inactive'])) {
      $message = t('user not active.') . l(t('goto validate'), 'user/' . $user->uid . '/sms_validation');
    }
    else {
      $message = token_replace($conf['message_inactive']);
    }
    $block->content = array(
      'message' => array(
        '#markup' => $message,
        '#prefix' => '<div class="message not-active">',
        '#suffix' => '</div>'
      ),
    );
  }
  return $block;
}

/**
 * Implements callback mymodule_myplugin_content_type_edit_form()
 */
function sms_validation_sms_validation_pane_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['message_not_logged'] = array(
    '#type' => 'textarea',
    '#title' => t('Message Not Logged'),
    '#default_value' => isset($conf['message_not_logged']) ? $conf['message_not_logged'] : '',
    '#description' => t('The message show the SMS validation information on not logged'),
  );

  $form['message_inactive'] = array(
    '#type' => 'textarea',
    '#title' => t('Message Inactive'),
    '#default_value' => isset($conf['message_inactive']) ? $conf['message_inactive'] : '',
    '#description' => t('The message show the SMS validation information on inactive'),
  );
  $form['message_active'] = array(
    '#type' => 'textarea',
    '#title' => t('Message Active'),
    '#default_value' => isset($conf['message_active']) ? $conf['message_active'] : '',
    '#description' => t('The message show the SMS validation information on actived'),
  );

  if (module_exists('token')) {
    $form['view']['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      //      '#description' => t('Prefer raw-text replacements for text to avoid problems with HTML entities!'),
    );
    $form['view']['token_help']['help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node'),
    );
  }
  return $form;
}

/**
 * Validate the settings.
 */
function sms_validation_sms_validation_pane_content_type_edit_form_validate($form, &$form_state) {
}

/**
 * Submit handler
 */
function sms_validation_sms_validation_pane_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['message_not_logged'] = $form_state['values']['message_not_logged'];
  $form_state['conf']['message_inactive'] = $form_state['values']['message_inactive'];
  $form_state['conf']['message_active'] = $form_state['values']['message_active'];
}
