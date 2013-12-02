<?php
/* vim:set softtabstop=4 shiftwidth=4 expandtab: */
/**
 *
 * LICENSE: GNU General Public License, version 2 (GPLv2)
 * Copyright 2001 - 2013 Ampache.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

define('NO_SESSION','1');
define('CLI', 1);

$path = dirname(__FILE__);
$prefix = realpath($path . '/../');
require_once $prefix . '/lib/init.php';
ob_end_flush();

use Ratchet\MessageComponentInterface;
use Ratchet\ConnectionInterface;

$verbose = false;
$port = 8100;

$cargv = count($_SERVER['argv']);
if ($cargv > 1) {
    for ($x = 1; $x < $cargv; $x++) {

        if ($_SERVER['argv'][$x] == "-v") {
            $operations_string .= "\n\t" . T_('- Verbose');
            $verbose = true;
        } 
        elseif ($_SERVER['argv'][$x] == "-p" && ($x + 1) < $cargv) {
            $port = intval($_SERVER['argv'][++$x]);
            $operations_string .= "\n\t" . T_('- Port ' . $port);
        }
    }
}

$app = new Ratchet\App('localhost', $port);
$brserver = new Broadcast_Server();
$brserver->verbose = $verbose;
$app->route('/broadcast', $brserver);
$app->route('/echo', new Ratchet\Server\EchoServer, array('*'));
$app->run();

function usage()
{
    echo T_("- WebSocket server -");
    echo "\n";
    echo T_("Usage: websocket_run.inc [-p {PORT}|-v]");
    echo "\n\t"; 
    echo "\n-p {PORT}\t";
    echo T_('Listening port, default 8100');
    echo "\n-v\t";
    echo T_('Verbose');
    echo "\n";
    echo "----------------------------------------------------------";
    echo "\n";
}

?>